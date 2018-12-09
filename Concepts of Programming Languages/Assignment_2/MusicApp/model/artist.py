from sqlalchemy import *
from sqlalchemy.orm import relationship, backref
from . import Base, session

band_artists = Table(
    'band_artists',
    Base.metadata,
    Column('band_artist_id', INTEGER, primary_key=True),
    Column('band_id', INTEGER, ForeignKey('artists.id')),
    Column('artist_id', INTEGER, ForeignKey('artists.id')),
)


class Artist(Base):
    __tablename__ = 'artists'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    songs = relationship('Song', back_populates='artist')

    artists = relationship(
        'Artist',
        secondary=band_artists,
        primaryjoin=id == band_artists.c.band_id,
        secondaryjoin=id == band_artists.c.artist_id,
        backref=backref('bands')
    )

    def play_all(self):
        songs = []

        for song in self.songs:
            songs.append(song)

        for band in self.bands:
            for song in band.songs:
                songs.append(song)

        from model import Song
        Song.play_song_list(songs)



    def delete(self):
        for song in self.songs:
            song.delete()
        session.delete(self)
        session.commit()

    @staticmethod
    def get_all():
        return session.query(Artist).order_by(Artist.name).all()

    @staticmethod
    def select_artist():
        artists = Artist.get_all()
        print('Artists:')
        for i, artist in enumerate(artists):
            print('\t%s: %s' % (i + 1, artist))
        artist_id = int(input('Select Artist(0 back): '))
        if artist_id > 0:
            return artists[artist_id - 1]

    @staticmethod
    def view_artists():
        artists = Artist.get_all()
        print('Artists:')
        for i, artist in enumerate(artists):
            artists = (
                "" if len(artist.artists) == 0 else "[ " + ", ".join([str(x.name) for x in artist.artists]) + " ]")
            print('\t%s: %s %s' % (i + 1, artist, artists))
        return artists

    @staticmethod
    def create(artist_list, song=None):
        artist = Artist()
        artist.name = input('Artist/Band Name: ')
        res = int(input('Artist or A Band? \n (0: Artist, 1: Band)'))
        if song is not None:
            artist.songs = [song]
        if res == 1:
            while True:
                print("Select Band Artists: (0: To Skip)")
                for i, artistx in enumerate(artist_list):
                    print('%s: %s' % (i + 1, artistx.name))

                res = int(input())
                if res == 0:
                    break
                artist.artists.append(artist_list[res - 1])
        session.add(artist)

    def __repr__(self):
        return self.name
