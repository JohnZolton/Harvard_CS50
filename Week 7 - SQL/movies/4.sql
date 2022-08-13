--write a SQL query to determine the number of movies with an IMDb rating of 10.0.
SELECT count(movie_id) from ratings where rating = 10;