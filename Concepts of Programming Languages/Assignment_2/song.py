from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String

Base = declarative_base()


class Song(Base):
    __tablename__ = 'songs'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    artist = Column(String)

    def __repr__(self):
        return "<Song(name='%s', artist='%s')>" % (
            self.name, self.artist)
