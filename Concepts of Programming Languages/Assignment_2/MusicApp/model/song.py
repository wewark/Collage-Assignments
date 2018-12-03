from sqlalchemy import Column, Integer, String
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship
from . import Artist, Base


class Song(Base):
    __tablename__ = 'songs'

    id = Column(Integer, primary_key=True)
    name = Column(String)

    artist_id = Column(Integer, ForeignKey('artists.id'))
    artist = relationship('Artist', back_populates='songs')

    def __repr__(self):
        return "<Song(name='%s', artist='%s')>" % (
            self.name, self.artist.name)
