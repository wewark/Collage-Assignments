from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import relationship
from . import Base, session


class Artist(Base):
    __tablename__ = 'artists'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    songs = relationship('Song', back_populates='artist')

    @staticmethod
    def get_all():
        return session.query(Artist).order_by(Artist.name).all()

    @staticmethod
    def view_artists():
        print('Artists:')
        for i, artist in enumerate(Artist.get_all()):
            print('\t%s: %s' % (i, artist))

    def __repr__(self):
        return self.name
