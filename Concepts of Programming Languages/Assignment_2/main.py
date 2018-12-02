from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from song import Song

def init_db_session():
	engine = create_engine('sqlite:///db/song.db', echo=False)
	Session = sessionmaker(bind=engine)
	return Session()

# Run one time to create new table
# Base.metadata.create_all(engine)

def main():
	session = init_db_session()
	
	menu = """1: Add Song
2: view Songs
"""

	while True:
		response = int(input(menu))
		if response == 1:
			song = Song()
			song.name = input('Song Name: ')
			song.artist = input('Artist Name: ')
			session.add(song)
			session.commit()
		elif response == 2:
			for song in session.query(Song).order_by(Song.name):
				print('%s - %s' % (song.name, song.artist))
		elif response == 0:
			break

if __name__ == "__main__":
	main()
