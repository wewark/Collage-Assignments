import os

from pygame import mixer
from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.orm import relationship

from . import Artist, Base, session


class Song(Base):
    __tablename__ = 'songs'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    path = Column(String)

    artist_id = Column(Integer, ForeignKey('artists.id'))
    artist = relationship('Artist', back_populates='songs')
    album_id = Column(Integer, ForeignKey('albums.id'))
    album = relationship('Album', back_populates='songs')

    def play(self):
        mixer.init()
        mixer.music.load(self.path)
        mixer.music.play()
        print('Playing %s' % self.name)
        input('Press any key to stop')
        mixer.music.stop()
    
    @staticmethod
    def play_song():
        songs = Song.view_songs()
        song_id = int(input('Select song (0 back): '))
        songs[song_id - 1].play()

    @staticmethod
    def get_all():
        return session.query(Song).order_by(Song.name).all()

    @staticmethod
    def view_songs():
        i = 1
        songs = Song.get_all()
        for song in songs:
            print('%s: %s' % (i, song))
            i += 1
        return songs
    
    @staticmethod
    def view_files():
        i = 1
        files = os.listdir('db/songs')
        for i, f in enumerate(files):
            print('%s: %s' % (i + 1, f))
        return files

    def __repr__(self):
        return "%s - %s" % (self.name, self.artist.name)
