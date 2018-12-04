from model import *


def main():
    menu = """1: Add Song
2: View Songs
3: Create Playlist
4: View Playlists
5: View Artists
6: Play Song
7: Play Playlist
0: exit
"""

    while True:
        res = int(input(menu))
        if res == 1:
            song = Song()
            song.name = input('Song Name: ')

            song_files = Song.view_files()
            file_id = int(input('Select song file: '))
            song.path = 'db/songs/%s' % song_files[file_id - 1]


            artist_list = []
            for artist in session.query(Artist).order_by(Artist.name):
                artist_list.append(artist)

            print('Select an artist:')
            print('0: Add new artist')
            for i, artist in enumerate(artist_list):
                print('%s: %s' % (i + 1, artist.name))

            res = int(input())
            if (res == 0):
                artist = Artist()
                artist.name = input('Artist Name: ')
                artist.songs = [song]
                session.add(artist)
            else:
                artist_list[res - 1].songs.append(song)
                session.add(artist_list[res - 1])

            session.commit()
        elif res == 2:
            Song.view_songs()
        elif res == 3:
            Playlist.create_playlist()
        elif res == 4:
            Playlist.view_playlists()
        elif res == 5:
            Artist.view_artists()
            input()
        elif res == 6:
            Song.play_song()
        elif res == 7:
            Playlist.select_and_play()
        elif res == 0:
            break


if __name__ == "__main__":
    main()
