import datetime
import time
import urllib2
import json

today = datetime.date.today()
time = time.strftime("%H:%M:%S")
releases = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases").read()
for release in json.loads(releases):
  id = release['name']
  total = 0
  total_unix = 0
  total_macos = 0
  total_windows = 0
  total_installers = 0
  for asset in release['assets']:
    download_count = asset['download_count']
    filename = asset['name']
    print '\"' + id + "\",\"" + str(today) + "\",\"" + str(time) + "\",\"" + filename  + "\"," + str(download_count)
    if filename.find('windows') >= 0:
      total_windows = total_windows + download_count
    if filename.find('macos') >= 0:
      total_macos = total_macos + download_count
    if filename.find('fedora')  >= 0 or filename.find('ubuntu') >= 0:
      total_unix = total_unix + download_count
    if filename.find('.zip')  >= 0 or filename.find('.exe') >= 0 or filename.find('.dmg') >= 0 or filename.find('dep') >= 0:
      total_installers = total_installers + download_count
    total = total + download_count
  print '\"' + id + "\",\"" + str(today) + "\",\"" + str(time) + "\",\"total_unix\"," + str(total_unix)
  print '\"' + id + "\",\"" + str(today) + "\",\"" + str(time) + "\",\"total_macos\"," + str(total_macos)
  print '\"' + id + "\",\"" + str(today) + "\",\"" + str(time) + "\",\"total_windows\"," + str(total_windows)
  print '\"' + id + "\",\"" + str(today) + "\",\"" + str(time) + "\",\"total_installers\"," + str(total_installers)
  print '\"' + id + "\",\"" + str(today) + "\",\"" + str(time) + "\",\"total\"," + str(total)

adstudio_releases = urllib2.urlopen("https://api.github.com/repos/admb-project/adstudio/releases").read()
for adstudio_release in json.loads(adstudio_releases):
  for asset in adstudio_release['assets']:
    download_count = asset['download_count']
    filename = asset['name']
    print '\"' + id + "\",\"" + str(today) + "\",\"" + str(time) + "\",\"" + filename  + "\"," + str(download_count)
