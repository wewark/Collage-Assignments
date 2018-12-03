from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import relationship
from . import Base


class Artist(Base):
    __tablename__ = 'artists'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    songs = relationship('Song', back_populates='artist')

    def __repr__(self):
        return "<Artist(name='%s')>" % (
            self.name)
