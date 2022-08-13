-- list names of any songs that have danceability, energy and valence > .75
SELECT name FROM songs WHERE danceability>.75 and energy>.75 and valence >.75;
