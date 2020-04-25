SELECT title from movies JOIN ratings ON movies.id = ratings.movie_id WHERE id IN (SELECT movie_id from stars WHERE person_id IN (SELECT id from people WHERE name = "Chadwick Boseman")) ORDER BY rating DESC LIMIT 5;