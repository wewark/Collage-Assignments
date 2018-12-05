from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import relationship
from . import Base, session


class Artist(Base):
    __tablename__ = 'artists'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    songs = relationship('Song', back_populates='artist')

    def play_all(self):
        for song in self.songs:
            song.play()

    @staticmethod
    def get_all():
        return session.query(Artist).order_by(Artist.name).all()

    @staticmethod
    def view_artists():
        artists = Artist.get_all()
        print('Artists:')
        for i, artist in enumerate(artists):
            print('\t%s: %s' % (i + 1, artist))
        return artists

    def __repr__(self):
        return self.name
