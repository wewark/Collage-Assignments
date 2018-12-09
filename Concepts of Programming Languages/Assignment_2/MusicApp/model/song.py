import os

from pygame import mixer
from sqlalchemy import *
from sqlalchemy.orm import relationship
from random import shuffle

from . import Base, session

song_features = Table('song_features', Base.metadata,
                      Column('song_id', Integer,
                             ForeignKey('songs.id')),
                      Column('artist_id', Integer, ForeignKey('artists.id')))


class Song(Base):
    __tablename__ = 'songs'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    path = Column(String)
    artist_id = Column(Integer, ForeignKey('artists.id'))
    artist = relationship('Artist', back_populates='songs')
    album_id = Column(Integer, ForeignKey('albums.id'))
    album = relationship('Album', back_populates='songs')
    genre = Column(String)
    date = Column(String)
    features = relationship('Artist', secondary=song_features)

    def play(self):
        mixer.init()
        mixer.music.load(self.path)
        mixer.music.play()
        print('Playing %s' % self.name)
        input('Press any key to stop')
        mixer.music.stop()
    
    def delete(self):
        session.delete(self)
        session.commit()

    @staticmethod
    def play_genre():
        genres = session.query(Song.genre).distinct().all()
        for i, genre in enumerate(genres):
            print('%s: %s' % (i + 1, genre[0]))
        genre_id = int(input('Select Genre(0 back)'))


        songs = []

        for song in session.query(Song).filter(Song.genre == genres[genre_id - 1][0]):
            songs.append(song)

        Song.play_song_list(songs)


    @staticmethod
    def play_song():
        song = Song.select_song()
        if song is not None:
            song.play()

    @staticmethod
    def get_all():
        return session.query(Song).order_by(Song.name).all()

    @staticmethod
    def print_all_songs():
        songs = Song.get_all()
        for i, song in enumerate(songs):
            print('%s: \t %s' % (i, song))

    @staticmethod
    def select_song():
        songs = Song.get_all()
        for i, song in enumerate(songs):
            print('%s: %s' % (i + 1, song))
        song_id = int(input('Select Song (0 back): '))
        if song_id > 0:
            return songs[song_id - 1]

    @staticmethod
    def view_files():
        i = 1
        files = os.listdir('db/songs')
        for i, f in enumerate(files):
            print('%s: %s' % (i + 1, f))
        return files

    @staticmethod
    def play_song_list(songs):
        shuffleFlag = int(input('Play mode: (0: normal, 1: shuffle)'))
        if shuffleFlag is 1:
            shuffle(songs)
        print("Playing...\nQueue:")
        for i, song in enumerate(songs):
            print('\t%s - %s\tby: %s' % (i, song.name, song.artist.name))
        for song in songs:
            print('Starting... \n%s - %s \tby %s' % (i, song.name, song.artist.name))
            song.play()

    def __repr__(self):
        ft = ""

        if len(self.features) > 0:
            ft = "(ft. "
            for arist in self.features:
                ft += arist.name + ", "
            ft = ft[0:len(ft)-2] + ")"

        return ('Title: %s \t| Album: %s \t|\t Artist: %s %s \t| Genre: %s \t| Date: %s' % (
             self.name, self.album.name, self.artist.name, ft, self.genre, self.date))
