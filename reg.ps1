Add-Content -Path C:\Users\client.LAB\Desktop\output.txt -Value (Select-String -Pattern "package=`"([^`"]{1,50})`"" -Path C:\Users\client.LAB\Desktop\app.txt).Matches.Groups[0].Value
