CREATE MASTER KEY ENCRYPTION BY PASSWORD = 'Str0ngPa$$'
GO

CREATE ASYMMETRIC KEY KeyProtector
WITH ALGORITHM = RSA_2048
ENCRYPTION BY PASSWORD = '@n0therStr0ngPa$$'
GO

CREATE SYMMETRIC KEY KeyForData
WITH ALGORITHM = AES_256
ENCRYPTION BY ASYMMETRIC KEY KeyProtector
GO

USE FilmLibrary

ALTER TABLE [dbo].[Контракты]
ADD [Дата_заключения_зашифр] varbinary(MAX)

GO

OPEN SYMMETRIC KEY KeyForData
DECRYPTION BY ASYMMETRIC KEY KeyProtector
WITH PASSWORD = '@n0therStr0ngPa$$'

USE FilmLibrary

UPDATE [dbo].[Контракты]
	SET [Дата_заключения_зашифр] = 
		ENCRYPTBYKEY(KEY_GUID('KeyForData'), CONVERT(varbinary(max), [Дата_заключения]))
	FROM [dbo].[Контракты];


CLOSE SYMMETRIC KEY KeyForData;

GO

CREATE VIEW [Контракты_расшифр] ([Номер_контракта], [Код_киностудии], [Код_актёра], [Дата_заключения_контракта])
WITH ENCRYPTION
AS 
	SELECT [Номер_контракта], [Код_киностудии], [Код_актёра],
		CONVERT(datetime, DECRYPTBYKEY([Дата_заключения_зашифр])) As [Дата_заключения_контракта]
	FROM [dbo].[Контракты]

GO

OPEN SYMMETRIC KEY KeyForData
DECRYPTION BY ASYMMETRIC KEY KeyProtector
WITH PASSWORD = '@n0therStr0ngPa$$'

SELECT * FROM [Контракты]

CLOSE SYMMETRIC KEY KeyForData;

GO

OPEN SYMMETRIC KEY KeyForData
DECRYPTION BY ASYMMETRIC KEY KeyProtector
WITH PASSWORD = '@n0therStr0ngPa$$'

SELECT * FROM [Контракты_расшифр]

CLOSE SYMMETRIC KEY KeyForData;