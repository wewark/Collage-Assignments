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
10: View Albums
11: Play Genre
12: Add Song to Playlist
13: Remove song from playlist
14: Delete Playlist
15: Delete Song
16: Delete Album
17: Delete Artist
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
            song.genre = input('Genre: ')
            song.date = input('Date: ')

            artist_list = session.query(Artist).order_by(Artist.name).all()

            print('Select an artist:')
            print('0: Add new artist')
            for i, artist in enumerate(artist_list):
                print('%s: %s' % (i + 1, artist.name))

            res = int(input())
            if res == 0:
                artist = Artist()
                artist.name = input('Artist Name: ')
                artist.songs = [song]
                session.add(artist)
            else:
                artist_list[res - 1].songs.append(song)
                session.add(artist_list[res - 1])

            #############

            print('Add feature ?')
            res = int(input("0: Yes 1: NO"))

            if res == 0:
                while True:
                    for i, artist in enumerate(artist_list):
                        print('%s: %s' % (i + 1, artist.name))

                    res = int(input())
                    song.features.append(artist_list[res - 1])
                    print('Add feature ?')
                    res = int(input("0: Yes 1: NO"))
                    if res == 1:
                        break
            session.add(song)

            ############

            album_name = input('Album Name: ')
            album = Album.find_or_create(album_name)
            album.songs.append(song)
            session.add(album)

            session.commit()
        elif res == 2:
            Song.print_all_songs()
            input("Press any key to return")
        elif res == 3:
            Playlist.create_playlist()
        elif res == 4:
            playlist = Playlist.select_playlist()
            if playlist is not None:
                print(playlist)
                input("Press any key to return")
        elif res == 5:
            Artist.view_artists()
            input("Press any key to return")
        elif res == 6:
            Song.play_song()
        elif res == 7:
            Playlist.select_and_play()
        elif res == 8:
            Artist.select_artist().play_all()
        elif res == 9:
            Album.select_and_play()
        elif res == 10:
            Album.view_albums()
        elif res == 11:
            Song.play_genre()
        elif res == 12:
            playlist = Playlist.select_playlist()
            if playlist is not None:
                playlist.add_song()
        elif res == 13:
            playlist = Playlist.select_playlist()
            if playlist is not None:
                playlist.remove_song()
        elif res == 14:
            playlist = Playlist.select_playlist()
            if playlist is not None:
                playlist.delete()
        elif res == 15:
            song = Song.select_song()
            if song is not None:
                song.delete()
        elif res == 16:
            album = Album.select_album()
            if album is not None:
                album.delete()
        elif res == 17:
            artist = Artist.select_artist()
            if artist is not None:
                artist.delete()
        elif res == 0:
            break


if __name__ == "__main__":
    main()
