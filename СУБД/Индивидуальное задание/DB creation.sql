USE [FilmLibrary]

CREATE TABLE [Актёр]
( 
	[Код_актёра] int  IDENTITY(1,1) ,
	[ФИО]             varchar(100)  NOT NULL ,
	[Дата_рождения] datetime  NULL ,
	[Город_проживания] varchar(50)  NULL ,
	CONSTRAINT [XPKАктёр] PRIMARY KEY  NONCLUSTERED ([Код_актёра] ASC)
)

CREATE TABLE [Фильм]
( 
	[Код_фильма] int  IDENTITY(1,1) ,
	[Название]   varchar(100)  NOT NULL ,
	[Длительность] int  NULL ,
	[Жанр]           varchar(50)  NULL ,
	[Год_выхода] int  NULL,
	CONSTRAINT [XPKФильм] PRIMARY KEY  NONCLUSTERED ([Код_фильма] ASC)
)


CREATE TABLE [Киностудия]
( 
	[Код_киностудии] int  IDENTITY(1,1) ,
	[Название]   varchar(100)  NOT NULL ,
	[Город_расположения] varchar(50)  NULL ,
	[Дата_основания] datetime  NULL ,
	CONSTRAINT [XPKКиностудия] PRIMARY KEY  NONCLUSTERED ([Код_киностудии] ASC)
)

CREATE TABLE [Актёр_Фильм]
( 
	[Код_актёра] int NULL ,
	[Код_фильма] int  NULL ,
)


CREATE TABLE [Киностудия_Фильм]
( 
	[Код_киностудии] int  NULL ,
	[Код_фильма] int  NULL ,
)

CREATE TABLE [Контракты]
( 
	[Номер_контракта] int  NOT NULL ,
	[Дата_заключения] datetime  NOT NULL ,
	[Код_киностудии] int  NULL,
	[Код_актёра] int NULL ,
	CONSTRAINT [XPKКонтракты] PRIMARY KEY  NONCLUSTERED ([Номер_контракта] ASC)
)