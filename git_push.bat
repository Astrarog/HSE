@echo off
	git --git-dir="C:\Users\Roman\Documents\HSE\.git" add .

	git --git-dir="C:\Users\Roman\Documents\HSE\.git" commit -m "Autosync from Laptop %date% %time%"

	git push
