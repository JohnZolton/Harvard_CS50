--write a SQL query to list the titles
-- of all movies in which both Johnny Depp and Helena Bonham Carter starred.

SELECT DISTINCT title
FROM movies
JOIN stars on movies.id = stars.movie_id
JOIN people on people.id = stars.person_id
WHERE name in ("Johnny Depp", "Helena Bonham Carter")
GROUP BY title
HAVING count(movies.id) > 1;