--write a SQL query to list the names of all people who starred in Toy Story.
SELECT  name
from movies
join stars on movies.id = stars.movie_id
join people on stars.person_id = people.id
WHERE title = "Toy Story";