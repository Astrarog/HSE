BACKUP DATABASE [FilmLibrary]
TO DISK = N'C:\Database\Database.bak'
	WITH NOINIT, SKIP,
	NAME = N'Full Database Backup',
STATS = 10

GO

/*Восстановить базу*/
USE [master]
RESTORE DATABASE [FilmLibrary]
FROM DISK = N'C:\Database\Database.bak'
	WITH FILE = 1, NOUNLOAD, 
	STATS = 10
GO