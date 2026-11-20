# ESP32 Control Panel

## 1. Flash the ESP32
1. Open `esp32_server.ino` in Arduino IDE (ESP32 board package installed).
2. Set `WIFI_SSID` and `WIFI_PASS`, upload.
3. Open Serial Monitor (115200) and note the IP address it prints.

## 2. Put the website on GitHub Pages
1. Create a new GitHub repository.
2. Upload `index.html` to the repository root.
3. Go to **Settings > Pages**, set Source to **Deploy from a branch**, choose `main` and `/ (root)`, then Save.
4. Your site appears at `https://<username>.github.io/<repo>/` after a minute.

## 3. Connect
Open the site, type the ESP32 IP, press **Connect**.

## Important: HTTPS vs HTTP
GitHub Pages is HTTPS, but the ESP32 serves plain HTTP. Browsers block this ("mixed content"). Fixes:
- **Chrome/Edge:** click the lock icon > Site settings > set **Insecure content** to *Allow*, then reload.
- **Firefox:** click the shield icon > turn off protection for this site.
- **Alternative:** open `index.html` directly from your computer (double-click) or via `http://localhost`.
- **Remote access / no browser tweaks:** use a Cloudflare Tunnel, or switch to MQTT over WebSockets (HTTPS-safe).

The ESP32 sketch already sends CORS headers so the browser accepts the cross-origin response.
