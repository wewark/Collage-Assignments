from sqlalchemy import Column, Integer, String, Table
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship
from . import Base, Song, session, SongCollection


class Playlist(SongCollection):
    __tablename__ = 'playlists'

    id = Column(Integer, ForeignKey('song_collection.id'), primary_key=True)

    __mapper_args__ = {
        'polymorphic_identity':'playlist',
    }

    @staticmethod
    def select_and_play():
        playlists = Playlist.get_all()
        for i, playlist in enumerate(playlists):
            print('%s: %s' % (i + 1, playlist.name))
        playlist_id = int(input('Select Playlist (0 back): '))
        playlists[playlist_id - 1].play()

    @staticmethod
    def get_all():
        return session.query(Playlist).order_by(Playlist.name).all()

    @staticmethod
    def view_playlists():
        playlists = Playlist.get_all()
        for i, playlist in enumerate(playlists):
            print('%s: %s' % (i + 1, playlist.name))

        playlist_id = int(input('Select Playlist (0 back): '))
        if playlist_id > 0:
            print(playlists[playlist_id - 1])
            input()

    @staticmethod
    def create_playlist():
        playlist = Playlist()
        playlist.name = input('Playlist Name: ')
        playlist.desc = input('Playlist Desc: ')

        Song.view_songs()
        songs = Song.get_all()
        while True:
            song_id = int(input('Song id (0 to finish): '))
            if song_id == 0:
                break
            playlist.songs.append(songs[song_id - 1])
        
        session.add(playlist)
        session.commit()

    def __repr__(self):
        ret = 'Playlist:\n'
        ret += 'Name: %s\n' % self.name
        ret += 'Desc: %s\n' % self.desc
        ret += 'Songs:'
        for song in self.songs:
            ret += '\n\t%s' % song
        return ret
