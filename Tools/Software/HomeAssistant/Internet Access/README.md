<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Internet Access

> Control Home Assistant Dashboard From Anywhere In The World

[Home Assistant](https://www.home-assistant.io/) runs as a local service in your private network and is accessible through a local ip address (or its default *mDNS* name *homeassistant.local*) on port 8123: `homeassistant.local:8123`.

Neither the *mDNS* hostname *homeassistant.local* nor port 8123 are publicly available from the outside.

If you'd like to manage *Home Assistant UI* from outside your private network - i.e. via smartphone while on vacation - you can set up *remote access*.

## Overview

[Accessing *Home Assistant* from abroad](https://www.home-assistant.io/docs/configuration/remote/) is possible via a number of routes:

* [Home Assistant Cloud/Remote UI:](https://www.home-assistant.io/docs/configuration/remote/) provided by the company that maintains *Home Assistant*. This is by far the easiest solution as it runs *out of the box*. However, this service [has significant cost attached](https://www.nabucasa.com/pricing/) (€7.50 per month or €75 per year as of this writing).
* [VPN:](https://openvpn.net/) By establishing a *VPN* (*virtual private network*) connection, you can access your local network from abroad. This is perfect if you have already set up *VPN*, and providers like [OpenVPN](https://openvpn.net/) offer free accounts.
* [Cloudflare Tunnel:](https://developers.cloudflare.com/learning-paths/replace-vpn/connect-private-network/) *Tunnels* work similar to *VPN* in that they allow secure access to your private network. *Cloudflare* is a renown US-based CDN and Internet Security company that offers *free accounts* that allow you to set up a *tunnel*. Combined with the add-on [CloudFlared](https://github.com/brenner-tobias/addon-cloudflared), this resembles a technically robust and *free* solution. You do need to own a *domain name* (or register one). Domain registration starts at €5/year. 
* **Port forwarding:** this is *insecure* and not recommended since you are making a *port* publicly available at your *Router*. It adds a *dangerous attack surface* since now *anyone in the world* has access to your *Home Assistant login page* and can try to break in or exploit possible bugs. In addition, most *Internet Service Providers* assign *dynamic IP addresses* to private customers that change often, so you would have to take additional provisions to *know* what your currently assigned *IP address* at home is.

**If you don't mind the monthly charge**, then *Home Assistant Cloud* is probably the easiest, safest, and most complete type of remote access. Accessing via [Remote UI](https://www.nabucasa.com/config/remote/) just requires a *paid Nabu Casa account* and setting up the [Home Assistant Cloud](https://www.nabucasa.com/config/) (see the provided links for details).

**If you are looking for a *free* service** and just need remote access to the *Home Assistant front-end*, then the *Cloudflare tunnel* in combination with the *Home Assistant add-on [CloudFlared](https://github.com/brenner-tobias/addon-cloudflared)* is probably the second best solution.

> [!NOTE]
> Setting up a *Cloudflare tunnel* to remotely access the *Home Assistant UI* is very simple and explained below. For more advanced features, i.e. allowing devices or your smartphone to send back sensor data to *Home Assistant* via the *tunnel* while remotely connected, more advanced *tunnel configuration* is required that is beyond the scope of this article.

## Using Cloudflare Tunnel

These are the steps it takes to set up a *basic Home Assistant remote access* based on a *free Cloudflare tunnel*:


* **Grant permission:** in *Home Assistant*, grant permission to your *add-ins* so they may act as a *proxy* for you. 
* **Visit Cloudflare:** create a *free Cloudflare account*, register a domain name, and switch the domain DNS to be managed by *Cloudflare*.
* **Install Cloudflared:** install the *Home Assistant add-on CloudFlared*, and tell it the *domain name* you want to use for external access. The add-on does the rest and creates the *tunnel*.
* **Authorize Tunnel:** Authorize the new tunnel in your *Cloudflare Dashboard*, and associate it with the *domain* that you want to use for *remotely accessing Home Assistant*. 

Once done, you can access your *Home Assistant Dashboard* from anywhere in the world by entering the *domain name* you registered into any browser window, or by using the official *Home Assistant app*.



## Configure Home Assistant
Let's start with this step first as it requires a little bit of advanced *Home Assistant configuration*. All the remaining steps are simple click-work.


<details><summary>Why is this step needed anyway? Is it dangerous?</summary><br/>


When accessing *Home Assistant* remotely, you need someone at the *local Home Assistant instance in your home* that can act on your behalf: a *puppet* (or more technically a *proxy*).

The *Home Assistant CloudFlared* acts as such a proxy. *Home Assistant* needs to *trust* it, and it doesn't trust *anybody* by default.

Granting such permissions is nothing a regular user would do on a regular basis, so there are no controls in the user interface for it.

To grant the permission, you need to *manually* add the appropriate lines into *Home Assistants'* main configuration file named *configuration.yaml*.

For this you need a *file editor* which can be added to *Home Assistant* as an *add-on*. Once you have a *file editor* at hand, editing *configuration.yaml* and adding the permission is simple.

Whenever you edit core settings, the primary risk is that you *mess up vital settings* as there is no *UI* to guide and prevent you from accidentally shooting yourself in the knee.

That's why the guide below makes sure you *test* and *validate* your changes to *configuration.yaml* before you apply them.

> [!CAUTION]
> That said, as always, it is completely up to you and solely at your own risk to apply changes to your instance of *Home Assistant* or generally follow any advice given on this website.

</details>

1. Install a *editor add-on* if you have no file editor installed on your *Home Assistant*. Click below link to install *Studio Code Server* (based on *VSCode*), or install any other file editor of your choice.

    [<img src="images/show_addon_ha.svg" width="40%" height="40%" />](https://my.home-assistant.io/redirect/supervisor_addon/?addon=a0d7b954_vscode)

2. If you installed *Studio Code Server*, click *Studio Code Server* in the *Home Assistant sidebar*. Else, open any other *file editor* you may be using.

3. In your *file editor*, open the file `/config/configuration.yaml`. This file may be completely empty, or it may already contain content. If it does, **do not change** any of its existing content. *Append* the lines below to the end of the file:

     ````
     http:
      use_x_forwarded_for: true
      trusted_proxies:
        - 172.30.33.0/24
      ip_ban_enabled: true
      login_attempts_threshold: 5
     ````

     * **use_x_forwarded_for:** Uses the *X-Forwarded-For* header from the proxy to know real client IP.
     * **trusted_proxies:** trusts the *docker network* where the *add-ons* are located
     * **ip_ban_enabled:** bans IP addresses based on login attempts. *(optional)*
     * **login_attempts_threshold:** bans *IP addresses* after the number of consecutive failed login attempts. *(optional)*

     <img src="images/studio_code_server_http_cloudflared.png" width="100%" height="100%" />

     > Make sure you get the *indendation* right. *Studio Code Editor* shows squiggles and tooltips if your indentation is incorrect, but other editors may not double-check for you. *Studio Code Server* also applies your edits to the file immediately. There is no need to *save* edits.

3. In the *Home Assistant sidebar*, click *Developer tools*, then make sure the tab *YAML* at the top of the page is selected. Click *CHECK CONFIGURATION*. Assert that your edits won't prevent *Home Assistant* from starting.


    <img src="images/5_validate_configuration_cloudflared.png" width="100%" height="100%" />

4. Click *RESTART*, then *Restart Home Assistant* to fully restart *Home Assistant*.



## Signing Up With CloudFlare
Create a new free account with [CloudFlare](https://dash.cloudflare.com/sign-up). 

An overview of its services and what you can do with your account can be found [here](https://developers.cloudflare.com/fundamentals/setup/), but this reading or any  expertise with *Cloudflare* is not required.

Just stay logged into your *Cloudflare account* and follow  the next steps  up a free *remote access* for *Home Assistant*.


### Register Domain Name
Register a new domain name with [United Domains](https://www.united-domains.de/),  [Namecheap](https://www.namecheap.com/), or any other registrar.


> [!IMPORTANT]
> "Free" domain names from services like [FreeNom](https://www.freenom.com/) do not work.


You can register a new domain from inside *Cloudflare* as well, in which case you do not need to  switch *DNS* for your domain to *Cloudflare* separately (and can skip the next section) as it is by default using *Cloudflare DNS*.

<img src="images/1_register_domain_cloudflare.png" width="100%" height="100%" />

> [!NOTE]
> Choose a less popular *domain name*: *fredslittlehomeautomation.online* currently costs just €3 for the first year whereas *myhome.cloud* is available for €9.554.



### Add Domain DNS To Cloudflare
If you got your *domain* from a registrar other than *Cloudflare*, switch the *DNS* for it to *Cloudflare* so *Cloudflare* can manage it:

1. Log into your *Cloudflare dashboard*, and in the sidebar click *Websites*. 
2. lick *Add a site* to add your domain name. Follow the instructions.

## Install Add-On "Cloudflared"

On *Home Assistant*, install the *add-on Cloudflared*. 



<details><summary>What does "Cloudflared" do? Do I really need it?</summary><br/>

[Cloudflared](https://github.com/brenner-tobias/addon-cloudflared) is a free and open-source add-on for *Home Assistant* - you can [visit](https://github.com/brenner-tobias/addon-cloudflared) its project page and review its source code if in doubt.

You don't necessarily *need* this *add-on*. It just makes things so much easier. Without it, you would have to define the *tunnel* yourself, and you would have to take provisions on the *Home Assistant* side so that it would respond to the *tunnel*.

In a nutshell, *CloudFlared* is your local *proxy* that acts on your behalf whenever you access *Home Assistant* remotely: 

You enter the *Cloudflare tunnel* with your *registered domain name*, and at the other end, *Cloudflared* receives your commands and sends back the requested information.




</details>


Here are the three steps required:

* **Add-On Store:** make sure the add-on is available in the *Home Assistant Add-On Store*
* **Install:** install the add-on from the store
* **Configure:** set the domain name that you want to use to externally access *Home Assistant*
* **Launch Add-On:** launch the add-on, let it auto-create the tunnel, and authorize it in your *Cloudflare dashboard*

### Make Cloudflared Add-On Available
The add-on [Cloudflared](https://github.com/brenner-tobias/addon-cloudflared) is not part of the "official" *Home Assistant* add-ons. To be able to *install* it in the *Home Assistant Add-On Store*, it first must be added to the list of available add-ons:

1. Click the link below to navigate to the list of custom *urls* that can be installed via *Home Assistant Add-On Store*:

    [<img src="images/add_cloudflare_addon.svg" width="40%" height="40%" />](https://my.home-assistant.io/redirect/supervisor_add_addon_repository/?repository_url=https%3A%2F%2Fgithub.com%2Fbrenner-tobias%2Fha-addons)


1. A confirmation dialog opens. Verify that the local link to your *Home Assistant* in the bottom part of the dialog is correct. The link should point to `http://homeassistant.local:8123`. If it points to an *IP address*, make sure *Home Server* is currently using this address, or click the pencil icon to change the url.

    <img src="images/2_install_cloudflare_tunnel.png" width="60%" height="60%" />

2. When you are certain the *url* in the dialog is correct, click *Open link*. You are connected to *Home Assistant* and see the *Manage add-on repositories* page. The textbox *Add* is pre-populated with the *url* for the add-on you need. Click *ADD*.

    <img src="images/3_add_cloudflare_tunnel.png" width="60%" height="60%" />

3. The *source url* for the new *add-on* is added to your *custom add-ons* in your *Add-On Store*. Click *CLOSE* to close the dialog.

    <img src="images/4_installed_cloudflare_tunnel.png" width="60%" height="60%" />


> [!NOTE]
> You have just *added the source location* of the *add-on* to your *Add-On Store* so you can later *install* it. The *add-on* is at this point not yet installed (see next step).


### Install Cloudflared Add-On
Next, *install* the *cloudflared* add-on:

1. In the *Home Assistant sidebar*, click *Settings*, then *Add-ons*. This opens a page with all of your currently installed *add-ons*.

    <img src="images/6_add_on_store_cloudflared.png" width="100%" height="100%" />

2. Click *ADD-ON STORE* to open the store, and search for *cloudflared*. Thanks to the previous step, this "inofficial" *add-on* is discovered.

    <img src="images/7_select_cloudflared.png" width="100%" height="100%" />

3. Click the *add-on tile*. At the bottom of the tile, click *INSTALL*.

    <img src="images/8_invoke_install_cloudflared.png" width="100%" height="100%" />

4. The installation takes only a few seconds. Once it is installed, **do not start the add-on yet**.

    <img src="images/9_cloudflared_install_done.png" width="60%" height="60%" />


### Configure Cloudflared
Teach *cloudflared* the *domain name* you want to use to access *Home Assistant*. For this, in the *add-on page*, at the top click *Configuration*.



1. If you have closed the browser already or would like to return to this step at a later time, here is how you re-open the window: in the *Home Assistant sidebar*, click *Settings*, then *Add-ons*, then click on *Cloudflared*.

   <img src="images/10_cloudflared_configure_domain.png" width="100%" height="100%" />

2. In the text box *External Home Assistant Hostname*, enter the name of the *domain* you registered. Then click *SAVE*.

    <img src="images/11_start_cloudflared.png" width="100%" height="100%" />


### Launch Cloudflared
*Start* the add-on *cloudflared*:

1. At the top, click the tab *Info*, then turn on the options *Start on boot* and *Watchdog* to make sure the *add-on* is always available. Finally, in the bottom part click *START*.


    <img src="images/12_authorize_cloudflared.png" width="100%" height="100%" />

2. At the top, click *Log* and scroll to the bottom where you find a *cloudflare url* that you need to visit to authorize the tunnel. Copy and paste the *url* into your browser, and log into your *Cloudflare account*.

    <img src="images/13_authorize_cloudflared.png" width="100%" height="100%" />

3. Inside *Cloudflare*, you are then asked to select the *domain* you wish to assign to the tunnel (if you use more than one). *Cloudflare* automatically creates a *certificate* that is picked up by the *cloudflared add-on*, and you are set.

    <img src="images/14_cloudflared_view_log.png" width="100%" height="100%" />

4. You can switch back to the *Log* tab to view this part from *cloudflared's perspective*.

> [!IMPORTANT]
> In *Cloudflare Dashboard*, you can enable of additional *security features* to protect access. Start by following the security advisor, and at minimum make sure *Cloudflare* enforces *https* access. Do **not** use *http* to access *Home Assistant*.

## Accessing Home Assistant Remotely

If you followed all steps, you can now access your instance of *Home Assistant* remotely from anywhere in the world. 

Simply launch a browser, and enter the domain name you used above:

<img src="images/15_login_remotely_to_ha.png" width="100%" height="100%" />

You are greeted with the *Home Assistant login* and can now use your credentials to log into *Home Assistant* - just as if you would use it locally inside your home network.

<img src="images/16_using_cloudflared_with_ha_remotely.png" width="100%" height="100%" />


> Tags: Home Assistant, Internet, Access, Cloudflare, Cloudflared, Proxy, Remote Access

[Visit Page on Website](https://done.land/tools/software/homeassistant/internetaccess?705421071514241948) - created 2024-07-13 - last edited 2024-07-13
