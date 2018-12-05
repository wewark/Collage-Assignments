from sqlalchemy import Column, Integer, String, Table
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship
from . import Base, Song, session, SongCollection


class Album(SongCollection):
    __tablename__ = 'albums'

    id = Column(Integer, ForeignKey('song_collection.id'), primary_key=True)

    __mapper_args__ = {
        'polymorphic_identity':'album',
    }

    def __init__(self, name):
        self.name = name

    @staticmethod
    def find_or_create(name):
        album = session.query(Album).filter_by(name=name).first()
        if album is None:
            album = Album(name)
        return album

    @staticmethod
    def select_and_play():
        albums = Album.get_all()
        for i, album in enumerate(albums):
            print('%s: %s' % (i + 1, album.name))
        album_id = int(input('Select Album (0 back): '))
        album[album_id - 1].play()

    @staticmethod
    def get_all():
        return session.query(Album).order_by(Album.name).all()

    @staticmethod
    def view_albums():
        albums = Album.get_all()
        for i, album in enumerate(albums):
            print('%s: %s' % (i + 1, album.name))

        album_id = int(input('Select Album (0 back): '))
        if album_id > 0:
            print(albums[album_id - 1])
            input()

    @staticmethod
    def create_album():
        album = Album()
        album.name = input('Album Name: ')
        album.desc = input('Album Desc: ')

        Song.view_songs()
        songs = Song.get_all()
        while True:
            song_id = int(input('Song id (0 to finish): '))
            if song_id == 0:
                break
            album.songs.append(songs[song_id - 1])
        
        session.add(album)
        session.commit()

    def __repr__(self):
        ret = 'Album:\n'
        ret += 'Name: %s\n' % self.name
        ret += 'Desc: %s\n' % self.desc
        ret += 'Songs:'
        for song in self.songs:
            ret += '\n\t%s' % song
        return ret
