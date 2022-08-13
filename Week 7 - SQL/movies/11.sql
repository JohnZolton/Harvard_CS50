-- write a SQL query to list the titles of the five highest rated movies (in order)
--that Chadwick Boseman starred in, starting with the highest rated.

SELECT DISTINCT title
from movies
JOIN stars on movies.id = stars.movie_id
JOIN ratings on movies.id = ratings.movie_id
JOIN people on people.id = stars.person_id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;