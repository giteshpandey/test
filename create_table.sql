/*use database wtl;

CREATE TABLE IF NOT EXISTS trade_order ( id varchar(20) not null ,  book_id varchar(20) not null, event_time timestamp, price double, quantity double, constraint pk_order primary key (id,book_id)  );
