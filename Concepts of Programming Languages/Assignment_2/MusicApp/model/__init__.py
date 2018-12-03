from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()

from model.artist import Artist
from model.song import Song