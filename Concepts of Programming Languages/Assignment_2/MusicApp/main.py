# import sys
# import os
# sys.path.append(os.path.join(__file__, '..', '..'))

from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from model import *


def init_db_session():
    engine = create_engine('sqlite:///db/song.db', echo=False)
    Session = sessionmaker(bind=engine)
    # Run one time to create new table
    Base.metadata.create_all(engine)
    return Session()


def main():
    session = init_db_session()

    menu = """1: Add Song
2: view Songs
0: exit
"""

    while True:
        response = int(input(menu))
        if response == 1:
            song = Song()
            song.name = input('Song Name: ')

            artist_list = []
            for artist in session.query(Artist).order_by(Artist.name):
                artist_list.append(artist)
            
            print('Select an artist:')
            print('0: Add new artist')
            for i, artist in enumerate(artist_list):
                print('%s: %s' % (i + 1, artist.name))
            
            response = int(input())
            if (response == 0):
                artist = Artist()
                artist.name = input('Artist Name: ')
                artist.songs = [song]
                session.add(artist)
            else:
                artist_list[response - 1].songs.append(song)
                session.add(artist_list[response - 1])
            
            session.commit()
        elif response == 2:
            for song in session.query(Song).order_by(Song.name):
                print('%s - %s' % (song.name, song.artist.name))
        elif response == 0:
            break


if __name__ == "__main__":
    main()
