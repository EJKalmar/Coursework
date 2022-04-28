--a)
select route_number, sum(num_routes) from
	(select route_number, 0 as num_routes from routes
	union
	select route_number,count(route_number) as num_routes from sailings group by route_number) as T1
		group by route_number order by route_number;

--b)
select vessel_name, count(vessel_name) as num_sailings from sailings
	group by vessel_name order by vessel_name;

--c)
select route_number, count(route_number) as num_vessels from
	(select distinct route_number, vessel_name from sailings order by route_number) as T1
		 group by route_number having count(route_number) >=2 order by route_number;

--d)
select distinct route_number, vessel_name, year_built from fleet natural join sailings natural join
	(select distinct route_number, min(year_built) as year_built from sailings natural join fleet
		group by route_number) as T1 order by route_number;

--e)
select distinct vessel_name from sailings natural join
	(select distinct source_port from fleet natural join sailings where vessel_name = 'Coastal Renaissance'
	union
	select distinct destination_port from fleet natural join sailings where vessel_name = 'Coastal Renaissance')
		as T1 order by vessel_name;

--f)
with max_unique_vessels as
	(select max(unique_vessels) from
		(select route_number, count(distinct vessel_name) as unique_vessels from sailings group by route_number)
			as T1)
select route_number, count(distinct vessel_name) as num_vessels from sailings group by route_number
	having count(distinct vessel_name) = (select * from max_unique_vessels);

--g)
select port, route_number, sum(sailings) as sailings from
	(select route_number, source_port as port, count(route_number) as sailings from sailings group by route_number, source_port
	union
	select route_number, destination_port as port, count(route_number) as sailings from sailings group by route_number, destination_port)
		as T1 group by port, route_number order by port;

--h)
with partg as
	(select port, route_number, sum(sailings) as sailings from
	(select route_number, source_port as port, count(route_number) as sailings from sailings group by route_number, source_port
	union
	select route_number, destination_port as port, count(route_number) as sailings from sailings group by route_number, destination_port)
		as T1 group by port, route_number order by port)
	select port, route_number, sailings from partg natural join
		(select port, max(sailings) as sailings from partg group by port) as T1
		order by port;

		select distinct S1.vessel_name, S2.vessel_name,
			count(*) over(partition by S1.vessel_name,S2.vessel_name) as num_pairings
			from sailings as S1 join sailings as S2 on S1.route_number = S2.route_number
				and S1.source_port = S2.destination_port
				and S2.destination_port = S1.source_port
				and S1.scheduled_departure = S2.scheduled_departure
				and S1.vessel_name < S2.vessel_name
			order by num_pairings desc;

--i)
select distinct route_number, nominal_duration,
	avg(extract(epoch from arrival) - extract(epoch from scheduled_departure))
	over(partition by route_number)/60
	from sailings natural join routes;

--j)
with sailing_dates as
(select distinct extract(year from scheduled_departure) as year,
	extract(month from scheduled_departure) as month, extract(day from scheduled_departure) as day
	from sailings where route_number = 1 order by year, month, day),
late_counts as(
select extract(year from scheduled_departure) as year,
	extract(month from scheduled_departure) as month,
	extract(day from scheduled_departure) as day,
	count(*) over(partition by extract(year from scheduled_departure),
	extract(month from scheduled_departure), extract(day from scheduled_departure))
	as late_count
	from sailings natural join routes
	where (extract(epoch from arrival) - extract(epoch from scheduled_departure))/60-nominal_duration >=5
	and sailings.route_number = 1)
select distinct month, count(day) over(partition by month) from
	sailing_dates natural left outer join late_counts where late_count is null;

--k)
with total_sailings as(
	select distinct vessel_name, count(*) over(partition by vessel_name) as total_sailings
	from sailings),
late_sailings as(
	select distinct vessel_name, count(*) over(partition by vessel_name) as late_sailings
	from sailings natural join routes
	where (extract(epoch from arrival) - extract(epoch from scheduled_departure))/60-nominal_duration >=5)
select vessel_name, total_sailings, late_sailings,
		cast(late_sailings as decimal)/total_sailings as late_fraction
	from total_sailings natural join late_sailings order by vessel_name;

--l)
select distinct vessel_name, count(*) over(partition by vessel_name) as made_up_sailings
	from sailings natural join routes
	where extract(epoch from actual_departure)/60 - extract(epoch from scheduled_departure)/60 >= 15
	and extract(epoch from arrival)/60 - extract(epoch from scheduled_departure)/60 - nominal_duration <= 5
	order by vessel_name;
