from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base


def init_db_session():
    engine = create_engine('sqlite:///db/song.db', echo=False)
    Session = sessionmaker(bind=engine)
    # Run one time to create new table
    Base.metadata.create_all(engine)
    return Session()


Base = declarative_base()
session = init_db_session()

from model.artist import Artist
from model.song import Song
from model.playlist import Playlist
