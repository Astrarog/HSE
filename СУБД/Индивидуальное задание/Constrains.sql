-- Функция для упрощения --
CREATE FUNCTION nullOrNonEmpty (@data varchar(20))
RETURNS bit
AS
BEGIN
    IF (@data IS NULL OR @data > '')          
        RETURN CAST(1 AS bit)
	RETURN CAST(0 AS bit)
END

GO

USE [FilmLibrary]
-- Ограничения на данные --

ALTER TABLE [Актёр] ADD 
	CONSTRAINT [Актёр_уже_родился] CHECK ([Дата_рождения] < GETDATE()),
	CONSTRAINT [Актёр_родился_после_появления_фильмов] CHECK (YEAR([Дата_рождения]) > 1800),
	CONSTRAINT [Если_есть_ФИО_то_оно_не_пусто] CHECK (dbo.nullOrNonEmpty([ФИО]) = 1),
	CONSTRAINT [Если_есть_Город_то_он_не_пуст] CHECK (dbo.nullOrNonEmpty([Город_проживания]) = 1)

ALTER TABLE [Фильм] ADD 
	CONSTRAINT [Фильм_вышел_или_скоро_выйдет] CHECK ([Год_выхода] < YEAR(GETDATE())+20),
	CONSTRAINT [Фильм_вышел_появления_фильмов] CHECK (YEAR([Год_выхода]) > 1800),
	CONSTRAINT [Если_есть_Название_то_оно_не_пусто] CHECK (dbo.nullOrNonEmpty([Название]) = 1),
	CONSTRAINT [Если_есть_Жанр_то_он_не_пуст] CHECK (dbo.nullOrNonEmpty([Жанр]) = 1),
	CONSTRAINT [Если_есть_Длительность_то_она_не_пуста] CHECK ([Длительность] IS NULL OR [Длительность] > 0)


ALTER TABLE [Киностудия] ADD 
	CONSTRAINT [Киностудия_основана_или_скоро_будет] CHECK ([Дата_основания] < YEAR(GETDATE())+20),
	CONSTRAINT [Киностудия_появилась_после_появления_фильмов] CHECK (YEAR([Дата_основания]) > 1800),
	CONSTRAINT [Если_есть_Название_Киностудии_то_оно_не_пусто] CHECK (dbo.nullOrNonEmpty([Название]) = 1),
	CONSTRAINT [Если_есть_Город_расположения_то_он_не_пуст] CHECK (dbo.nullOrNonEmpty([Город_расположения]) = 1)

GO

-- При удалении контракта и связей Many-Many выставляем данные в NULL, чтобы  сохранить информацию о контракте/связи --
-- Когда обе стороны контракта в NULL (или оба поля таблицы M-M), то срабатывает триггер на удаление сущности --

ALTER TABLE [Контракты] ADD
	CONSTRAINT [Контракты_при_удалении_Киностудии] FOREIGN KEY ([Код_киностудии]) REFERENCES [Киностудия]([Код_киностудии])
		ON DELETE SET NULL
		ON UPDATE SET NULL ,
	CONSTRAINT [Контракты_при_удалении_Актёра] FOREIGN KEY ([Код_актёра]) REFERENCES [Актёр]([Код_актёра])
		ON DELETE SET NULL
		ON UPDATE SET NULL

ALTER TABLE [Актёр_Фильм] ADD
	CONSTRAINT [А_при_АФ_удалении] FOREIGN KEY ([Код_актёра]) REFERENCES [Актёр]([Код_актёра])
		ON DELETE SET NULL
		ON UPDATE SET NULL ,
	CONSTRAINT [Ф_при_АФ_удалении] FOREIGN KEY ([Код_фильма]) REFERENCES [Фильм]([Код_фильма])
		ON DELETE SET NULL
		ON UPDATE SET NULL

ALTER TABLE [Киностудия_Фильм] ADD
	CONSTRAINT [К_при_КФ_удалении] FOREIGN KEY ([Код_киностудии]) REFERENCES [Киностудия]([Код_киностудии])
		ON DELETE SET NULL
		ON UPDATE SET NULL ,
	CONSTRAINT [Ф_при_КФ_удалении] FOREIGN KEY ([Код_фильма]) REFERENCES [Фильм]([Код_фильма])
		ON DELETE SET NULL
		ON UPDATE SET NULL
-- TO DO: TRIGGERS --
GO