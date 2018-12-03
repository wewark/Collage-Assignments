from sqlalchemy import Column, Integer, String
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship
from . import Artist, Base, session


class Song(Base):
    __tablename__ = 'songs'

    id = Column(Integer, primary_key=True)
    name = Column(String)

    artist_id = Column(Integer, ForeignKey('artists.id'))
    artist = relationship('Artist', back_populates='songs')

    @staticmethod
    def get_all_songs():
        return session.query(Song).order_by(Song.name).all()

    @staticmethod
    def view_songs():
        i = 1
        for song in session.query(Song).order_by(Song.name):
            print('%s: %s' % (i, song))
            i += 1

    def __repr__(self):
        return "%s - %s" % (self.name, self.artist.name)
