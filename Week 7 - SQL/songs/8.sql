--write a SQL query that lists the names of the songs that feature other artists.
SELECT name from songs WHERE name LIKE '%feat.%';