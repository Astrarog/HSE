-- Функция для упрощения --
GO
CREATE FUNCTION notNullAndNotEmpty (@data varchar(20))
RETURNS bit
AS
BEGIN
    IF (@data IS NOT NULL OR @data > '')          
        RETURN CAST(1 AS bit)
	RETURN CAST(0 AS bit)
END

GO

-- Ограничения на данные --
USE [FilmLibrary]
 
ALTER TABLE [Актёр] ADD 
	CONSTRAINT [Актёр_уже_родился] CHECK ([Дата_рождения] IS NULL OR [Дата_рождения] < GETDATE()),
	CONSTRAINT [Актёр_родился_после_появления_фильмов] CHECK ([Дата_рождения] IS NULL OR YEAR([Дата_рождения]) > 1800),
	CONSTRAINT [ФИО_не_пусто] CHECK (dbo.notNullAndNotEmpty([ФИО]) = 1)

ALTER TABLE [Фильм] ADD 
	CONSTRAINT [Фильм_вышел_или_скоро_выйдет] CHECK ([Год_выхода] IS NUll OR [Год_выхода] < YEAR(GETDATE())+20),
	CONSTRAINT [Фильм_вышел_после_появления_фильмов] CHECK ([Год_выхода] IS NULL OR YEAR([Год_выхода]) > 1800),
	CONSTRAINT [Название_Фильма_не_пусто] CHECK (dbo.notNullAndNotEmpty([Название]) = 1),
	CONSTRAINT [Если_есть_Длительность_то_она_не_пуста] CHECK ([Длительность] IS NULL OR [Длительность] > 0)


ALTER TABLE [Киностудия] ADD 
	CONSTRAINT [Киностудия_основана_или_скоро_будет] CHECK ([Дата_основания] IS NUll OR YEAR([Дата_основания]) < YEAR(GETDATE())+20),
	CONSTRAINT [Киностудия_появилась_после_появления_фильмов] CHECK ([Дата_основания] IS NULL OR YEAR([Дата_основания]) > 1800),
	CONSTRAINT [Название_Киностудии_не_пусто] CHECK (dbo.notNullAndNotEmpty([Название]) = 1)

GO

/*  
	При удалении контракта и связей Many-Many выставляем данные в NULL,
    чтобы  сохранить информацию о контракте/связи
    Когда обе стороны контракта в NULL (или оба поля таблицы M-M), 
	то срабатывает триггер на удаление сущности 
*/
ALTER TABLE [Контракты] ADD
	CONSTRAINT [Контракты_при_удалении_Киностудии] FOREIGN KEY ([Код_киностудии]) REFERENCES [Киностудия]([Код_киностудии])
		ON DELETE SET NULL
		ON UPDATE CASCADE,
	CONSTRAINT [Контракты_при_удалении_Актёра] FOREIGN KEY ([Код_актёра]) REFERENCES [Актёр]([Код_актёра])
		ON DELETE SET NULL
		ON UPDATE CASCADE

ALTER TABLE [Актёр_Фильм] ADD
	CONSTRAINT [А_при_АФ_удалении] FOREIGN KEY ([Код_актёра]) REFERENCES [Актёр]([Код_актёра])
		ON DELETE SET NULL
		ON UPDATE CASCADE,
	CONSTRAINT [Ф_при_АФ_удалении] FOREIGN KEY ([Код_фильма]) REFERENCES [Фильм]([Код_фильма])
		ON DELETE SET NULL
		ON UPDATE CASCADE

ALTER TABLE [Киностудия_Фильм] ADD
	CONSTRAINT [К_при_КФ_удалении] FOREIGN KEY ([Код_киностудии]) REFERENCES [Киностудия]([Код_киностудии])
		ON DELETE SET NULL
		ON UPDATE CASCADE,
	CONSTRAINT [Ф_при_КФ_удалении] FOREIGN KEY ([Код_фильма]) REFERENCES [Фильм]([Код_фильма])
		ON DELETE SET NULL
		ON UPDATE CASCADE
GO

CREATE TRIGGER [NULL_проверка_после_удаления_Актёра]
ON [dbo].[Актёр] AFTER DELETE 
AS
BEGIN
	DELETE FROM [Актёр_Фильм] WHERE [Код_актёра] IS NULL AND [Код_фильма] IS NULL
	DELETE FROM [Контракты] WHERE [Код_актёра] IS NULL AND [Код_киностудии] IS NULL
END
GO

CREATE TRIGGER [NULL_проверка_после_удаления_Фильма]
ON [dbo].[Фильм] AFTER DELETE 
AS
BEGIN
	DELETE FROM [Актёр_Фильм] WHERE [Код_актёра] IS NULL AND [Код_фильма] IS NULL
	DELETE FROM [Киностудия_Фильм] WHERE [Код_киностудии] IS NULL AND [Код_киностудии] IS NULL
END
GO

CREATE TRIGGER [NULL_проверка_после_удаления_Киностудии]
ON [dbo].[Киностудия] AFTER DELETE 
AS
BEGIN
	DELETE FROM [Контракты] WHERE [Код_актёра] IS NULL AND [Код_киностудии] IS NULL
	DELETE FROM [Киностудия_Фильм] WHERE [Код_киностудии] IS NULL AND [Код_киностудии] IS NULL
END
GO