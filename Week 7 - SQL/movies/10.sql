--write a SQL query to list the names of
--all people who have directed a movie that received a rating of at least 9.0.

SELECT distinct name
from movies
join directors on movies.id = directors.movie_id
join ratings on movies.id = ratings.movie_id
join people on directors.person_id = people.id
WHERE rating >= 9.0;