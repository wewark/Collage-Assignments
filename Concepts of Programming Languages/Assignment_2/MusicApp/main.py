from model import *


def main():
    menu = """1: Add Song
2: View Songs
3: Create Playlist
4: View Playlists
5: View Artists
6: Play Song
7: Play Playlist
8: Play Artist Songs
9: Play Album
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

            artist_list = session.query(Artist).order_by(Artist.name).all()

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
            
            album_name = input('Album Name: ')
            album = Album.find_or_create(album_name)
            album.songs.append(song)
            session.add(album)

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
        elif res == 8:
            artists = Artist.view_artists()
            artist_id = int(input('Select Artist(0 back): '))
            if artist_id > 0:
                artists[artist_id - 1].play_all()
        elif res == 9:
            Album.select_and_play()
        elif res == 0:
            break


if __name__ == "__main__":
    main()
