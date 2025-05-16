# Video_Demand

drop database if exists aod_system;
create database if not exists aod_system;
use aod_system;
create table if not exists tb_video(
    id int primary key auto_increment,
    name varchar(32),
    info text,
    video varchar(256),
    image varchar(256)
);