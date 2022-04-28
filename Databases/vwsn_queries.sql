--(a) Find the highest observed temperature in the dataset, along with the station number, station
--name and observation time of all cases where that temperature was reported.
--Note: The expected output below is correct (that is, the observation shown is actually in the
--dataset, even though it appears to be unseasonably warm).
with max_temp as(
	select max(temperature) from observations)
select station_id, name, temperature, observation_time from
	observations join stations on observations.station_id = stations.id natural join max_temp
		where temperature = max_temp.max;

--(b) For each station with station ID between 1 and 10 (inclusive), list the station ID, station name,
--maximum temperature observed at that station and observation time of all observations in
--the dataset in which the maximum temperature was attained at that station. Only include
--stations which actually have recorded observations in the dataset.
with max_temps as
	(select distinct station_id, max(temperature) over (partition by station_id) as max_temp
	from observations where station_id >= 1 and station_id <=10)
select station_id, name, temperature as max_temperature, observation_time from
	observations join stations on observations.station_id = stations.id natural join max_temps
	where temperature = max_temps.max_temp order by station_id;

--c)
select distinct station_id, name from observations join stations on observations.station_id = stations.id
except
select station_id, name from observations join stations on observations.station_id = stations.id
	where extract(year from observation_time) = 2020
	and extract(month from observation_time) = 1;

--d)
with avg_daily_temps as(
select extract(year from observation_time) as year, extract(month from observation_time) as month,
	extract(day from observation_time) as day,
	avg(temperature) as avg_daily_temp
	from observations group by extract(year from observation_time), extract(month from observation_time),
	extract(day from observation_time)),
avg_temp_ranks as(
select *, rank() over(partition by month order by avg_daily_temp) as cool_rank,
	rank() over(partition by month order by avg_daily_temp desc) as hot_rank from
	avg_daily_temps),
hottest_10 as(
select year, month, avg_daily_temp as hottest_10 from avg_temp_ranks
	where hot_rank <=10),
coolest_10 as(
select year, month, avg_daily_temp as coolest_10 from avg_temp_ranks
	where cool_rank <=10)
select distinct year, month, avg(hottest_10.hottest_10) over (partition by year, month) as hottest10_average,
	avg(coolest_10.coolest_10) over (partition by year, month) as coolest10_average
	from hottest_10 natural join coolest_10 order by year,month;

--e)
with avg_daily_temps as(
select rank () over(order by extract(year from observation_time), extract(month from observation_time),
	extract(day from observation_time)),
	extract(year from observation_time) as year, extract(month from observation_time) as month,
	extract(day from observation_time) as day,
	avg(temperature) as avg_daily_temp
	from observations group by extract(year from observation_time), extract(month from observation_time),
	extract(day from observation_time)),
min_prev28 as(
	select *, case when rank >=28 then
			min(avg_daily_temp) over (order by year, month, day rows between 28 preceding and 1 preceding)
			else null end as min_prev28
		from avg_daily_temps)
select year, month, day from min_prev28
	where avg_daily_temp < min_prev28 order by year, month, day;
