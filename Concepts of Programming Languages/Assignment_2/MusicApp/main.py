from model import *


def main():
    menu = """1: Add Song
2: View Songs
3: Create Playlist
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
            Song.view_songs()
        elif response == 3:
            Playlist.create_playlist()
        elif response == 0:
            break


if __name__ == "__main__":
    main()
