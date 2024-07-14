<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Internet Access

> Control Home Assistant Dashboard From Anywhere In The World

[Home Assistant](https://www.home-assistant.io/) runs as a local service in your private network and is accessible through a local ip address (or its default *mDNS* name *home.assistant*) at port 8123.

If you'd like to visit the *Home Assistant UI* from outside your private network - i.e. via your smartphone while you are on vacation - you can set up *remote access*.

## Overview

[Accessing *Home Assistant* from abroad](https://www.home-assistant.io/docs/configuration/remote/) is possible via a number of routes:

* [Home Assistant Cloud/Remote UI:](https://www.home-assistant.io/docs/configuration/remote/) provided by the company that maintains *Home Assistant*. This is by far the easiest solution as it runs *out of the box*. However, this service [has substantial cost attached](https://www.nabucasa.com/pricing/) (€7.50 per month or €75 per year as of this writing).
* [VPN:](https://openvpn.net/) By establishing a *VPN* (*virtual private network*) connection, you can access your local network from abroad. This is perfect if you have already set up *VPN*, and providers like [OpenVPN](https://openvpn.net/) provide free accounts.
* [Cloudflare Tunnel:](https://developers.cloudflare.com/learning-paths/replace-vpn/connect-private-network/) *Tunnels* work similar to *VPN* in that they allow secure access to your private network. *Cloudflare* is a renown US-based CDN and Internet Security company that offers *free accounts* enabling you to set up a *tunnel*. Combined with a matching [Home Assistant integration](https://github.com/brenner-tobias/addon-cloudflared), this resembles a technically robust and *free* solution. You do need to own a *domain name* or register one. Any domain name will do. Domain registration starts at €5/year. 
* **Port forwarding:** this is *insecure* and not recommended since you are making a *port* publicly available at your *Router*. It adds a *dangerous attack surface* since now *anyone in the world* can access this port and try and break into your *home automation systems*. On top, most *Internet Service Providers* assign *dynamic IP addresses* to private customers, so you would have to set up additional services in order to *know* what the currently assigned *IP address* of your home is.

If you don't mind the monthly charge, then *Home Assistant Cloud* is probably the easiest, safest, and most complete type of remote access you can get. Accessing *Home Assistant* via its built-in [Remote UI](https://www.nabucasa.com/config/remote/) just requires a *paid Nabu Casa account* and setting up the [Home Assistant Cloud](https://www.nabucasa.com/config/). Setting this up is well explained in the links provided above and not covered here in any more detail.

If all you need is using the web based *Home Assistant front-end* from abroad, and you are not asking for devices or your phone to sending back sensor data while being away from your home network, then the *Cloudflare tunnel* in combination with the *Home Assistant add-on **cloudflared*** is probably the second best solution.

Since the latter requires a few configuration steps on your part, setting it up is explained in great detail below.

## Using Cloudflare Tunnel

Here are the configuration steps to set up a *Cloudflare tunnel* to remotely access *Home Assistant* in a browser:

* **Grant permission:** in *Home Assistant*, grant permission for the *add-on cloudflared* to act as a *proxy* for you. This is the most technical part as this permission is not controllable via simple controls in the user interface but requires adding a few lines to a *Home Assistant file*.
* **Cloudflare:** create a *free Cloudflare account*, register a domain name, and switch the domain DNS to *Cloudflare*.
* 



## Configure Home Assistant
This step is probably the hardest part because it involves editing a *Home Assistant file*. 

### Advanced Setting

This configuration step is necessary because the add-on *cloudflared* needs permission to send requests on your behalf - after all *cloudflared* is your *proxy* (or *puppet*) that does *locally* what you ask it to do *remotely* via the *tunnel*. 

Since such a permission setting is so rarely used, there is no control for it in the graphical user interface. Thus, you need a *file editor add-on*, enabling you to *manually edit Home Assistant files*. If you haven't installed one yet, check out add-ons like *File Editor* or *Studio Code Server*.

These prerequisites are really the hardest part, and I am starting with this so you can judge right away whether you want to proceed or give up. 

Cheer up, this step isn't really hard, and the remaining steps are really a piece of cake and just a few clicks. As a reward for your effort, you get an awesome and robust *Home Assistant remote access* - so don't feel discouraged easily. 

### Install Editor Add-On
If you haven't installed an editor add-on yet, you may want to look into add-ons like *File Editor* or *Studio Code Server*. Installing such add-ons is not part of this article and works no different from any other *add-on*.

### Granting Proxy Permission
Once the *editor add-on* is visible in the *Home Assistant sidebar*, this is what you do:

1. In *Home Assistant*, open a *file editor*. There is no file editor installed by default. You need to install a *file editor add-on* yourself.
2. In the *file editor*, open the file `/config/configuration.yaml`. This file may be empty, or may already have content. **Do not change** any content, and *append* this to the end of the file:

     ````
     http:
      use_x_forwarded_for: true
      trusted_proxies:
        - 172.30.33.0/24
     ````
3. In the *Home Assistant sidebar*, click *Developer tools*, then make sure the tab *YAML* at the top of the page is selected. Click *CHECK CONFIGURATION*. Make sure your edits won't prevent *Home Assistant* from starting.


    <img src="images/5_validate_configuration_cloudflared.png" width="100%" height="100%" />

4. Click *RESTART*, then *Restart Home Assistant* to fully restart *Home Assistant*.



## Signing Up With CloudFlare
Start by creating your new free account with [CloudFlare](https://dash.cloudflare.com/sign-up). 

> [!TIP]
> An overview of its services and what you can do with your account can be found [here](https://developers.cloudflare.com/fundamentals/setup/).


### Registering Domain Name
Register a new domain name with [United Domains](https://www.united-domains.de/),  [Namecheap](https://www.namecheap.com/), [GoDaddy](https://www.godaddy.com/) or any other registrar.


> [!IMPORTANT]
> "Free" domain names from services like [FreeNom](https://www.freenom.com/) do not work.


Once you signed up with *Cloudflare* and logged into the *Cloudflare dashboard*, you can register a new domain right there, too. In this case you do not need to separately switch *DNS* for the domain to *Cloudflare*.

<img src="images/1_register_domain_cloudflare.png" width="100%" height="100%" />

> [!NOTE]
> Save cost by choosing a less popular *domain name*: *fredslittlehomeautomation.online* currently costs €3 in first year whereas *myhome.cloud* is available for €9.554.



### Add Domain DNS To Cloudflare
Switch the *DNS* for your *domain* to *Cloudflare* so *Cloudflare* can manage it:

1. Log into your *Cloudflare dashboard*, and in the sidebar click *Websites*. 
2. lick *Add a site* to add your domain name. Follow the instructions.

## Install Add-On "Cloudflared"

On *Home Assistant*, install the *add-on Cloudflared*. It automatically creates the *Cloudflare tunnel* for you and acts as a *proxy*: it invokes *locally inside Home Assistant* what you requested *remotely*.

Here are the three steps required:

* **Add-On Store:** make sure the add-on is available in the *Home Assistant Add-On Store*
* **Install:** install the add-on from the store
* **Configure:** set the domain name that you want to use to externally access *Home Assistant*
* **Launch Add-On:** launch the add-on, let it auto-create the tunnel, and authorize it in your *Cloudflare dashboard*

### Make Cloudflared Add-On Available
The add-on [Cloudflared](https://github.com/brenner-tobias/addon-cloudflared) is not part of the "official" *Home Assistant* add-ons. To be able to *install* it in the *Home Assistant Add-On Store*, it first must be added to the list of available add-ons:



[<img src="images/add_cloudflare_addon.svg
" width="60%" height="60%" />](https://my.home-assistant.io/redirect/supervisor_add_addon_repository/?repository_url=https%3A%2F%2Fgithub.com%2Fbrenner-tobias%2Fha-addons)


1. A confirmation dialog opens. Make sure the local link to your *Home Assistant* in the bottom part of the dialog is correct. The link should point to `http://homeassistant.local:8123`. If it points to an *IP address*, make sure *Home Server* is currently using this address, or click the pencil icon to change the url.

    <img src="images/2_install_cloudflare_tunnel.png" width="100%" height="100%" />

2. When you are certain the *url* in the dialog is correct, click *Open link*. You are connected to *Home Assistant* and see the *Manage add-on repositories* page. The textbox *Add* is pre-populated with the *url* for the add-on you need. Click *ADD*.

    <img src="images/3_add_cloudflare_tunnel.png" width="100%" height="100%" />

3. The *source url* for the new *add-on* is added to your *custom add-ons* in your *Add-On Store*. Click *CLOSE* to close the dialog.

    <img src="images/4_installed_cloudflare_tunnel.png" width="100%" height="100%" />


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

    <img src="images/9_cloudflared_install_done.png" width="100%" height="100%" />


### Configure Cloudflared
Now it is time to teach *cloudflared* the *domain name* you want to use to access *Home Assistant*. For this, in the *add-on page*, at the top click *Configuration*.



1. If you have closed the browser already or would like to return to this step at a later time, here is how you re-open the window: in the *Home Assistant sidebar*, click *Settings*, then *Add-ons*, then click on *Cloudflared*.

   <img src="images/10_cloudflared_configure_domain.png" width="100%" height="100%" />

2. In the text box *External Home Assistant Hostname*, enter the name of the *domain* you registered. Then click *SAVE*.

    <img src="images/11_start_cloudflared.png" width="100%" height="100%" />


### Launch Cloudflared
Now it is time to *start* the add-on *cloudflared*:

1. At the top, click the tab *Info*, then turn on the options *Start on boot* and *Watchdog* to make sure the *add-on* is always available. Finally, in the bottom part click *START*.


    <img src="images/12_authorize_cloudflared.png" width="100%" height="100%" />

2. At the top, click *Log* and scroll to the bottom where you find a *cloudflare url* that you need to visit to authorize the tunnel. Copy and paste the *url* into your browser, and log into your *Cloudflare account*.

    <img src="images/13_authorize_cloudflared.png" width="100%" height="100%" />

3. Inside *Cloudflare*, you are then asked to select the *domain* you wish to assign to the tunnel (if you use more than one). *Cloudflare* automatically creates a *certificate* that is picked up by the *cloudflared add-on*, and you are set.

    <img src="images/14_cloudflared_view_log.png" width="100%" height="100%" />

4. You can switch back to the *Log* tab to view this part from *cloudflared's perspective*.

## Accessing Home Assistant Remotely

If you followed all steps, you can now access your instance of *Home Assistant* remotely from anywhere in the world. 

Simply launch a browser, and enter the domain name you used above:

<img src="images/15_login_remotely_to_ha.png" width="100%" height="100%" />

You are greeted with the *Home Assistant login* and can now use your credentials to log into *Home Assistant* - just as if you would use it locally inside your home network.

<img src="images/16_using_cloudflared_with_ha_remotely.png" width="100%" height="100%" />


> Tags: Home Assistant, Internet, Access, Cloudflare, Cloudflared, Proxy, Remote Access

[Visit Page on Website](https://done.land/tools/software/homeassistant/internetaccess?705421071514241948) - created 2024-07-13 - last edited 2024-07-13
