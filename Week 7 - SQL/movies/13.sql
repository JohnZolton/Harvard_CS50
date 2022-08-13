--write a SQL query to list the names of all
--people who starred in a movie in which Kevin Bacon also starred.

SELECT DISTINCT name
from people
WHERE id in (
    --get person_id
    SELECT person_id
    FROM stars
    WHERE
    movie_id in
        --gets movie ids that kevin bacon starred in
        (SELECT movie_id
        FROM stars
        WHERE person_id =
            -- gets person ID of kevin bacon
            (SELECT id
            FROM people
            WHERE name = "Kevin Bacon" and birth = "1958")))
    and name != "Kevin Bacon";