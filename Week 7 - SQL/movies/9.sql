--write a SQL query to list the names of all people who starred
--in a movie released in 2004, ordered by birth year.

--join movie and stars tables
SELECT DISTINCT name
from movies
join stars on movies.id = stars.movie_id
join people on stars.person_id = people.id
WHERE year = 2004
ORDER BY birth;