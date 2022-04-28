--(a) For each year between 2000 and 2017 (inclusive), list the primary name, production year,
--rating and number of votes of the film or films which attained the highest rating among all
--movies produced in that year which received at least 10000 votes. Both the rating and number
--of votes are stored in the ratings table.
with max_ratings as(
	select distinct year, max(rating) over(partition by year) as max_rating
	from titles natural join ratings where title_type = 'movie' and votes >= 10000)
select name, title_type,year, rating, votes
	from max_ratings natural join ratings
		natural join titles natural join title_names
		where year>= 2000 and year <= 2017 and title_type = 'movie'
		and rating = max_rating and votes >= 10000 and is_primary
	order by year;

--(b) Select the primary name and episode count of each TV series (contained in the tv_series
--table) for which at least 6000 episodes have been produced.
select name as series_name, count as episode_count from (
select distinct series_id, count(title_id) over (partition by series_id) from tv_series natural join series_episodes
	natural join title_names where is_primary order by series_id) as T1
		join
	title_names on T1.series_id = title_names.title_id
	where count>=6000 order by count desc;

--c)
with
	primary_names as (select title_id, name as primary_name
		from title_names where is_primary = true)
select primary_name, year, title_id from primary_names natural join titles
	where year = 1989 and length_minutes = 180 and title_type = 'tvSpecial';

--d)
with
	primary_names as (select title_id, name as primary_name
		from title_names where is_primary = true)
select primary_name, year, length_minutes from primary_names natural join titles
	where length_minutes >=4320 and title_type = 'movie' order by length_minutes desc;

--c)
with
	primary_names as (select title_id, name as primary_name
		from title_names where is_primary = true)
select primary_name, year, length_minutes from primary_names
	natural join titles natural join cast_crew natural join people
		where year <= 1985 and name = 'Meryl Streep' and title_type = 'movie';

--e)
with
	primary_names as (select title_id, name as primary_name
		from title_names where is_primary = true)
select primary_name, year, length_minutes from primary_names natural join titles natural join
		(select title_id from title_genres where genre = 'Film-Noir'
		intersect
		select title_id from title_genres where genre = 'Action') as T1 order by primary_name;

--f)
with
	primary_names as (select title_id, name as primary_name
		from title_names where is_primary = true),
	dieharddirectors as (select person_id from primary_names natural join cast_crew natural join titles natural join directors
		where primary_name = 'Die Hard' and title_type = 'movie'),
	diehardwriters as (select person_id from primary_names natural join cast_crew natural join titles natural join writers
		where primary_name = 'Die Hard' and title_type = 'movie')
select name from people natural join
	(select * from dieharddirectors
	union
	select * from diehardwriters) as T1 order by name;

--g)
with
	primary_names as (select title_id, name as primary_name
		from title_names where is_primary = true),
	streep_films as (select title_id from people natural join cast_crew natural join titles
		where name = 'Meryl Streep' and title_type = 'movie'),
	hanks_films as (select title_id from people natural join cast_crew natural join titles
		where name = 'Tom Hanks' and title_type = 'movie')
select primary_name, year, length_minutes from primary_names natural join titles natural join
	(select * from streep_films
	intersect
	select * from hanks_films) as T1 order by primary_name;
