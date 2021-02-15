USE [FilmLibrary]

CREATE TABLE [Актёр]
( 
	[Код_актёра] int  IDENTITY(1,1) ,
	[ФИО]             varchar(20)  NOT NULL ,
	[Дата_рождения] datetime  NULL ,
	[Город_проживания] varchar(20)  NULL ,
	CONSTRAINT [XPKАктёр] PRIMARY KEY  NONCLUSTERED ([Код_актёра] ASC)
)

CREATE TABLE [Фильм]
( 
	[Код_фильма] int  NOT NULL ,
	[Название]   varchar(20)  NOT NULL ,
	[Длительность] int  NULL ,
	[Жанр]           varchar(20)  NULL ,
	[Год_выхода] int  NULL,
	CONSTRAINT [XPKФильм] PRIMARY KEY  NONCLUSTERED ([Код_фильма] ASC)
)


CREATE TABLE [Киностудия]
( 
	[Код_киностудии] int  IDENTITY(1,1) ,
	[Название]   varchar(20)  NOT NULL ,
	[Город_расположения] varchar(20)  NULL ,
	[Дата_основания] datetime  NULL ,
	CONSTRAINT [XPKКиностудия] PRIMARY KEY  NONCLUSTERED ([Код_киностудии] ASC)
)

CREATE TABLE [Актёр_Фильм]
( 
	[Код_актёра] int  NOT NULL ,
	[Код_фильма] int  NOT NULL ,
	CONSTRAINT [XPKАктёр_Фильм] PRIMARY KEY  CLUSTERED ([Код_актёра] ASC, [Код_фильма] ASC)
)



CREATE TABLE [Киностудия_Фильм]
( 
	[Код_киностудии] int  NOT NULL ,
	[Код_фильма] int  NOT NULL ,
	CONSTRAINT [XPKКиностудия_Фильм] PRIMARY KEY  CLUSTERED ([Код_киностудии] ASC,[Код_фильма] ASC)
)


CREATE TABLE [Контракты]
( 
	[Номер_контракта] int  NOT NULL ,
	[Дата_заключения] datetime  NOT NULL ,
	[Код_киностудии] int  NULL,
	[Код_актёра] int NULL ,
	CONSTRAINT [XPKКонтракты] PRIMARY KEY  NONCLUSTERED ([Номер_контракта] ASC)
)
