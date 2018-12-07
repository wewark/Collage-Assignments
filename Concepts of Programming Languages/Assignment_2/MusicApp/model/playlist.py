from sqlalchemy import Column, Integer, String, Table
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship
from . import Base, Song, session
from random import shuffle

playlist_song = Table('playlist_song', Base.metadata,
                      Column('playlist_id', Integer,
                             ForeignKey('playlists.id')),
                      Column('song_id', Integer, ForeignKey('songs.id')))


class Playlist(Base):
    __tablename__ = 'playlists'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    desc = Column(String)
    songs = relationship('Song', secondary=playlist_song)

    def play(self):
        shuffleFlag = int(input('Play mode: (0: normal, 1: shuffle)'))
        songs = []

        for song in self.songs:
            songs.append(song)

        if shuffleFlag is 1:
            shuffle(songs)
        for song in songs:
            song.play()

    def add_song(self):
        selectedSong = Song.select_song()
        self.songs.append(selectedSong)
        session.commit()

    def remove_song(self):
        song = self.select_song()
        if song is not None:
            self.songs.remove(song)
            session.commit()
    
    def delete(self):
        session.delete(self)
        session.commit()
    
    def select_song(self):
        for i, song in enumerate(self.songs):
            print('%s: %s' % (i + 1, song))
        song_id = int(input('Select song to remove (0 back): '))
        if song_id > 0:
            return self.songs[song_id - 1]

    @staticmethod
    def select_and_play():
        playlists = Playlist.get_all()
        for i, playlist in enumerate(playlists):
            print('%s: %s' % (i + 1, playlist.name))
        playlist_id = int(input('Select Playlist (0 back): '))
        playlists[playlist_id - 1].play()

    @staticmethod
    def get_all():
        return session.query(Playlist).order_by(Playlist.name).all()

    @staticmethod
    def select_playlist():
        playlists = Playlist.get_all()
        for i, playlist in enumerate(playlists):
            print('%s: %s [%s Tracks]' % (i + 1, playlist.name, len(playlist.songs)))

        playlist_id = int(input('Select Playlist (0 back): '))
        if playlist_id > 0:
            return playlists[playlist_id - 1]

    @staticmethod
    def create_playlist():
        playlist = Playlist()
        playlist.name = input('Playlist Name: ')
        playlist.desc = input('Playlist Desc: ')

        songs = Song.get_all()
        for i, song in enumerate(songs):
            print('%s: %s' % (i + 1, song))
        while True:
            song_id = int(input('Song id (0 to finish): '))
            if song_id == 0:
                break
            playlist.songs.append(songs[song_id - 1])

        session.add(playlist)
        session.commit()

    def __repr__(self):
        ret = 'Playlist:\n'
        ret += 'Name: %s\n' % self.name
        ret += 'Desc: %s\n' % self.desc
        ret += 'Songs: (%s Track)' % len(self.songs)
        i = 0
        for song in self.songs:
            ret += '\n\t%s' % song
            i = i+1
        return ret
