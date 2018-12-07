from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import relationship
from . import Base, session
from random import shuffle


class Artist(Base):
    __tablename__ = 'artists'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    songs = relationship('Song', back_populates='artist')

    def play_all(self):
        shuffleFlag = int(input('Play mode: (0: normal, 1: shuffle)'))
        songs = []

        for song in self.songs:
            songs.append(song)

        if shuffleFlag is 1:
            shuffle(songs)
        for song in songs:
            song.play()
    
    def delete(self):
        for song in self.songs:
            song.delete()
        session.delete(self)
        session.commit()

    @staticmethod
    def get_all():
        return session.query(Artist).order_by(Artist.name).all()
    
    @staticmethod
    def select_artist():
        artists = Artist.get_all()
        print('Artists:')
        for i, artist in enumerate(artists):
            print('\t%s: %s' % (i + 1, artist))
        artist_id = int(input('Select Artist(0 back): '))
        if artist_id > 0:
            return artists[artist_id - 1]

    @staticmethod
    def view_artists():
        artists = Artist.get_all()
        print('Artists:')
        for i, artist in enumerate(artists):
            print('\t%s: %s' % (i + 1, artist))
        return artists

    def __repr__(self):
        return self.name
