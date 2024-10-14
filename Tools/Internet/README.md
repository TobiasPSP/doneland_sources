<img src="/assets/images/butler.jpg" width="80%" height="80%" />
 
# Slow Website

> Why This Website May Be Loading Slow For You, And What You Can Do To Boost Your Internet 

We operate a modern and *very fast* website backed by state-of-the-art *content delivery networks* (*CDN*). Wherever you are located around the globe, this website should load in a snap and not take longer than a second.

Still, *a few users* experience **very slow** transfer rates, rendering this website almost unusable. These users typically are located in *Germany* and use *Deutsche Telekom* as *ISP* (or one of its spin-offs).

If you are affected by a slow website experience, this is **not related to this particular website**. While most websites work well, every now and then you will come across websites (and downloads) that are much slower than expected. The severity of the issue may also vary during the day or over time.

In this article, I'll explain the reasons, and what you can do about it to fix this issue. This won't just speed up *this* website: it will generally provide you with a much snappier, robust and enjoyable *Internet experience*.

If your hair is on fire, below is a quick summary.

> [!TIP]
> Some *ISPs* like the *Deutsche Telekom* (and affiliated *ISPs* who are using the same infrastructure) are notorious for causing *routing problems*: they point your requests to the origin of the website rather than the plenty of available local and fast *CDN mirror servers*. This affects websites that use certain *CDNs* only. Your choices are either to *change your ISP*, or to use a *VPN* like [NordVPN](https://refer-nordvpn.com/DdmJIprBMeZ) (the provided link adds a few free extra months for you (and me) - should you decide to sign up with them).

## Ingredients For Fast Internet Experience
Most users focus just on their *Internet Service Provider* (*ISP*) for *fast Internet speed*. High monthly fees get you a supposingly fast *Internet connection*, i.e. *250MBit/s* or even *1GBit/s*. You might discover though that occasionally, your Internet speed is much slower, and **a few** (not all) websites and downloads (as well as other services such as video conferences) perform sluggishly.

To understand why that is, you need to be aware that there are **two** crucial ingredients for fast Internet. Your *ISP Internet access* is just **one** of them:

* **Internet Service Provider (ISP):** the company that provides you with a *modem* and physically connects you to the *Internet*. *ISPs* are responsible for taking care of the **last mile**: connecting *your home or smartphone* with all the other networks in the *Internet*. Having a *fast ISP* is your ticket to *entering the Internet in a fast way*. It does not guarantee *fast transfer speeds* **inside** the *Internet*, though.  
* **Routing:** Once your data packages *enter* the *Internet* through your *ISP access point*, they need to get directions to travel to the desired target - similar to a navigation system in your car. That's called *Routing*. Routing is just as important as a fast *ISP*. It can send your packages to the nearest available *CDN server* (good), or it can route your packages across the globe to the *original webserver* (very bad).

> [!NOTE]
> View it this way: a *Ferrari* (aka *fast ISP*) won't win a race against a *Fiat* (aka *slow ISP*) when the *Ferarri's* navigation system (aka *Routing*) sends it back and forth and across the wildest dirt roads while the *Fiat navigation system* just takes the highway and uses the nearest exit.  

### Why *This* Website May Be Slow
The funny thing is that *bad routing* doesn't seem to affect *all websites* in the same way. That's why you are probably not aware of it at first. Here is why only *some* websites and downloads are affected:

This website is backed by sophisticated *CDNs* (*Content Delivery Networks*) and uses *static HTML* - all ingredients for *super fast and super responsive websites*. Routinely performed global audits underline that this website is among the top 5% speed-wise.

If pages still take painstakenly long to load **for you**, and if **you** see images appear only slowly line by line, or spot missing fonts or dearranged icons, then there can only be *three* potential issues:

* **Slow ISP/Bad Coverage:** Obviously, if you are using a *very slow ISP*, or if you are currently in an area with *very poor Internet coverage*, it is not surprising to experience slow Internet. In this case though, **all websites are slow**, not just *some*.
* **Slow Hoster:** theoretically, the operator of the Website (which would be *me*) could have choosen a *poor* service provider with slow download speeds and insufficient capacity. In this case, **everyone would experience a slow website**, not just a *few users*, and our auditing would generally show slow specs (which it doesn't).
* **Bad Routing:** if **you** experience a slow website while **others** enjoy lightning speed, then **your routing** is messed up: the data packets travel around the globe and take detours instead of the direct route, and this occurs both on the way *to* the website, and *back to you*. The majority of users enjoy *correct routing*, and for them, the website responds lightning fast.


## What Does Routing Do?
Without delving too much into networking, when you navigate to a website, your request is routed to the webserver hosting the website, and the website returns the website data back to you so your browser can display a page.

*Internet* uses *data packages* and sends them from server to server, starting with servers close to you, until the data packages finally arrive at the intended target.

So *Routing* on the internet is the process of selecting paths through which data can travel from *you* to the *target* (and vice versa) across many interconnected networks. It works much like a *navigation system* in your car.

### Visualizing Route
You can visualize the *hops* your data packages take, i.e. with `tracert.exe` on *Windows*. Below you see the *route* that was selected for me to reach *done.land*:

````
PS C:\> tracert done.land

Tracing route to done.land [172.67.130.250]
over a maximum of 30 hops:

  1    <1 ms    <1 ms    <1 ms  192.168.68.1
  2     1 ms    <1 ms    <1 ms  speedport.ip [192.168.2.1]
  3     6 ms     5 ms     5 ms  p3e9bf353.dip0.t-ipconnect.de [62.155.243.83]
  4    92 ms    92 ms    92 ms  nyc-sb6-i.NYC.US.NET.DTAG.DE [62.154.5.206]
  5   111 ms    96 ms    96 ms  80.156.160.213
  6    98 ms    98 ms    98 ms  if-ae-0-2.tcore3.njy-newark.as6453.net [216.6.90.14]
  7    97 ms    96 ms    97 ms  66.198.70.2
  8   103 ms    99 ms   100 ms  162.158.61.113
  9    98 ms    97 ms    97 ms  172.67.130.250

Trace complete.
````

My packages start to enter the *Internet* at IP address *62.155.243.83* in *Frankfurt/Main*:

````
PS> irm ipinfo.io/62.155.243.83/json


ip       : 62.155.243.83
hostname : p3e9bf353.dip0.t-ipconnect.de
city     : Frankfurt am Main
region   : Hesse
country  : DE
loc      : 50.1155,8.6842
org      : AS3320 Deutsche Telekom AG
postal   : 60306
timezone : Europe/Berlin
````

The target destination set by my *ISPs routing* is IP address *172.67.130.250* (my *CDN Cloudflare* in *Los Angeles*):

````
PS> irm ipinfo.io/172.67.130.250/json


ip       : 172.67.130.250
anycast  : True
city     : San Francisco
region   : California
country  : US
loc      : 37.7621,-122.3971
org      : AS13335 Cloudflare, Inc.
postal   : 94107
timezone : America/Los_Angeles
````

The data packages are taking many detours, i.e. hopping via *216.6.90.14*:
````
PS> > irm ipinfo.io/216.6.90.14/json


ip       : 216.6.90.14
hostname : if-ae-0-2.tcore3.njy-newark.as6453.net
city     : New York City
region   : New York
country  : US
loc      : 40.7143,-74.0060
org      : AS6453 TATA COMMUNICATIONS (AMERICA) INC
postal   : 10001
timezone : America/New_York
````

Aside from the high number of hops, this trace does not look alarming at first. I *am* apparently getting to the fast *CDN edge servers*, so I *should* receive a fast response. But is this true? 

Let's see next how the actual website behaves.


### Debugging Slow Website
Most modern browsers come with advanced debugging tools. In *Chrome* press `F12` to open its debug tools. Then click the tab *Network*, and empty the list of network requests.

Clear your browser cache before testing so you are measuring real download times rather than cached elements coming from your browser memory: in *Chrome*, click the *three-dot* menu, and choose *Delete browsing data...*. It is sufficient to delete the last *24 hours* of cached data.  

#### Navigate To Webpage Under Test
Now, enter the *url* of the website you want to test. I chose a random [*done.land* article](https://done.land/components/microcontroller/families/esp/esp32/lilygot-display/t-display) with a number of images and other resources. You can now watch the browser downloading all the web page data, and each downloaded resource lists its url, size, and time it took to download it:

<img src="images/routing_slow_website_chrome_debug_error.png" width="100%" height="100%" />

In this particular example, downloading the entire web page took insane *10.4 **minutes***. During this long time, just *1.8MB* of data was transferred. That is an average of *2800 bytes per second* on a *wired 250MBit/s ISP* internet connection.

When you look closely, the download wasn't even successful: one picture did not download and caused a timeout error: `ERR_QUIC_PROTOCOL_ERROR`.

Obviously, here is something seriously amiss: my *ISP* has routed my packets to the correct *CDN*, but has obviously targeted the *wrong* *CDN edge server*.

The *IP addresses* of the *edge servers* (the entry points to the *CDN*) are *dynamic* and can change frequently, primarily due to security and infrastructure reasons. I may be off, but apparently the *ISP* is not using the correct target *IP addresses* based on my location. We'll come back to this in a moment. 

Aside from the *why* and *how*, the website **is definitely impaired**, and the **reason is bad routing**.

### Border Gateway Protocol
*Routing* is complex and consists of many parts. Your *ISP* is responsible for the *Border Gateway Protocol* (*BGP*). It is used to exchange routing information between large networks, or "autonomous systems" (AS), such as *ISPs* (*Internet Service Providers*), big players (such as *AWS*), and most importantly *CDNs* (like *Cloudflare*).

Apparently, for many years now, some *ISPs* like the *Deutsche Telekom* in *Germany*, seem to have bad *Peering Agreements* (or do not update their information in a timely way): *ISPs* enter into peering agreements with each other to exchange traffic. If the ISP has poor peering relationships or high costs for certain routes, they might route traffic through less optimal or **outdated** paths, severely impacting speed. 

There are [plenty of discussions in German forums](https://telekomhilft.telekom.de/t5/Festnetz-Internet/Unglaublich-schlechtes-Routing/td-p/6827554) illustrating the problem.

> [!IMPORTANT]
> If you are experiencing slow *done.land* web pages, keep in mind that this is just a *symptom* of a larger problem. It is tricky because only certain networks and content delivery systems are affected. Even if you are not particular interested in *this site*, you may still want to fix your overall issue: you'll be surprised how much more enjoyable your *Internet experience* can become, and how much faster some downloads work.



## Solving the Issue
Since the fundamental *routing problem* is caused by the way how your *ISP* directs the data (and seems to ignore fast *CDNs*), you have two options:

* **Change ISP:** Change your current *ISP*, and choose a new *ISP*. This may be complicated and time-consuming because of contracts, infrastructure, and alike. Plus, you would need to make sure that your *new ISP* isn't using crucial infrastructure provided by your *old ISP*.
* **Use VPN:** The easiest solution is to use a *VPN* (*Virtual Private Network*). Basically, you exchange the *routing of your ISP* with the *routing of the VPN*.

### Using VPN
When you use a *VPN*, you still use your *ISP* for the *last mile*. However, you then access the nearest (and fastest) possible *VPN server* in your vicinity.

Your data packages then travel **anonymously** within the *VPN* server network. *VPNs* optimize routing for best speed, plus they also protect your *privacy* by anonymizing *IP addresses*. That's why *VPNs* are prohibited in most dictatorships (obviously not in *Europe* or the *US*). 

The downside of *VPNs* is that they are an additional *paid service* on top of your existing *ISP service*. But as you have seen, truly *fast and safe Internet access* consists of **two** things: a *fast last mile* (provided by your *ISP*),  **and** intelligent *routing* (not always provided by your *ISP*, can be added via a *VPN*).

> [!NOTE]
> You may be lucky, and your *ISP* may provide *fast clever routing* out of the box. Even then, using a *VPN* gives you so much more control, and may or may not still make sense for the added *security* and *privacy*.

As a *Deutsche Telekom* user in *Germany*, I was **severely** affected by the speed issues, so adding a *VPN* was a no-brainer, with the added *privacy* being a welcomed benefit. After some comparison, I opted for the basic (cheapest) [NordVPN package](https://refer-nordvpn.com/DdmJIprBMeZ) and purchased a *2-year contract* for around €90 in total (paid with own money, so no affiliation). Since it comes with a *30-day money back guarantee*, you can test whether it works for you and fixes potential speed problems. 

> By using this [NordVPN](https://refer-nordvpn.com/DdmJIprBMeZ) link, *you and me* both get a few free extra months. 

After testing, I found that *NordVPN* solved all my issues, and then some: I always had a few websites and downloads which funnily wouldn't perform as well as the rest. With *NordVPN*, now *all* my Internet resources load equally fast, finally letting my *expensive superfast ISP internet access* live up to its full potential. 

## Walkthrough: NordVPN
If you are wondering how a *VPN* works, and how you set it up, here is a quick walk-through on my first steps with [NordVPN](https://refer-nordvpn.com/DdmJIprBMeZ).

### Download NordVPN App
Your journey starts with downloading the [NordVPN app](https://nordvpn.com/download/). It is available for *Windows* and other operating systems as well as for smartphones.



<img src="images/nordvpn_1.png" width="50%" height="50%" />


After you installed the software, you find links on your *Desktop* and *Start Menu* (respective an *app icon* on your smartphone). When you start the *NordVPN* app, you can either *log in* or [create a NordVPN account (sign up)](https://refer-nordvpn.com/DdmJIprBMeZ). There are different *paid plans* and no *free tier*. 

If you have no *NordVPN* account yet, you might want to use [this link to sign up](https://refer-nordvpn.com/DdmJIprBMeZ) which provides *you and me* with a few free extra months.

When you click *Log in*, your browser opens and asks for your *username* and *password*. Once the browser-based authentication is done, you return to the *NordVPN app*.



### Select VPN Server
The *NordVPN app* shows your connection status: 

* **Not Connected:** **red** *Not Connected*, you are using your *ISPs* routing, and you see your currently assigned *IP address*.
* **Connected:** **green** *Connected*, you are using the *VPN* and its own routing. Your *ISP name* is no longer the *ISP* that connects your home to the Internet, and you are using anonymized *IP addresses*.

You can enter the *VPN* through a wealth of servers located around the globe. If you'd like to maximize your speed, choose a *VPN server* as close as possible to your current location. 

*Recent connections* (the top list) are your *favorites*. Initially, this list is randomly filled, so do not use *Quick Connect* or one of the servers in the top list.



<img src="images/nordvpn_3.png" width="100%" height="100%" />

Instead, in the *lower list* select the country where you are located. This adds the country to your *upper list* (your favorites), so from now on you can easily connect to a server in this country. 

To actually *connect* and start using the VPN, click the country in your top list.

> [!TIP]
> When you click the *three-dot menu* to the right of the selected country in the **lower** list, you see the available *cities* in the selected country. By default, *NordVPN* automatically selects the city with the fastest connection to you.

Once you are connected, you see your *country flag* and the currently active *ISP* at the top left side of your window.


<img src="images/nordvpn_4.png" width="30%" height="30%" />

## Results of fix
To see the effects of using *NordVPN*, let's repeat the website tests with the *VPN* active. Here is what the route now looks like:

````
PS> tracert done.land

Tracing route to done.land [188.114.97.4]
over a maximum of 30 hops:

  1    10 ms    10 ms    10 ms  10.5.0.1
  2    11 ms    11 ms    12 ms  185.161.202.2
  3     *       15 ms     *     185.161.202.3
  4     *       16 ms     *     ipv4.de-cix.ham.de.as13335.cloudflare.com [185.1.210.10]
  5    11 ms    11 ms    12 ms  188.114.97.4

Trace complete.
````


Within just *five **fast*** hops the data packages reach their destination. Note how the **destination IP address has changed**: it is now *188.114.97.4*:

````
PS> irm ipinfo.io/188.114.97.4/json


ip       : 188.114.97.4
anycast  : True
city     : San Francisco
region   : California
country  : US
loc      : 37.7621,-122.3971
org      : AS13335 Cloudflare, Inc.
postal   : 94107
timezone : America/Los_Angeles
````

This target IP address is *still* registered to *Cloudflare* located in *San Francisco*. But *registration data* is **not necessarily identical to where the actual server is located**. 

One hop before reaching the target, the trace reveals that we are hopping *ipv4.de-cix.ham.de.as13335.cloudflare.com* which is located in *Hamburg, Germany*, just around the corner from my location:

````
PS> irm ipinfo.io/185.1.210.10/json


ip       : 185.1.210.10
hostname : ipv4.de-cix.ham.de.as13335.cloudflare.com
city     : Hamburg
region   : Hamburg
country  : DE
loc      : 53.5507,9.9930
postal   : 20038
timezone : Europe/Berlin
````

In a nutshell, *VPN routing* has routed my data packets directly to the *closest available CDN server*, only a few kilometers away from where I live. The hops in-between (*185.161.202.2* and *185.161.202.3*) were also located right in *Hamburg*:

````
PS> irm ipinfo.io/185.161.202.2/json


ip       : 185.161.202.2
city     : Hamburg
region   : Hamburg
country  : DE
loc      : 53.5507,9.9930
org      : AS207137 PacketHub S.A.
postal   : 20038
timezone : Europe/Berlin
````

Keep in mind: before using *VPN*, my *ISP* had routed my packets all the way across the Atlantic ocean, and served the website from a different continent, with frequent total *packet loss*, resulting in extremely low speeds.

Let's verify the trace information, and look at the *real world consequences* this new routing has: I'll repeat the website test in my *Chrome* browser (don't forget to clear the browser cache before you test again). Remember: last time, it took over **10 minutes** to fully load the web page.

<img src="images/routing_slow_website_chrome_debug_vpn.png" width="100%" height="100%" />

This time, the same web page appears instantly. After mere *1.12s*, the complete web page and all of its images and fonts were loaded, and *2.7MB* were transfered. The transfer rate was *2.4MByte/s* (rather than 2.8KB/s as initially), almost *1000x* faster.

> Tags: Website, Slow, VPN, ISP, Routing, Cloudflare, NordVPN, Peering Agreement, Border Gateway Protocol, BGP, Telekom

[Visit Page on Website](https://done.land/tools/internet?015434101113241156) - created 2024-10-12 - last edited 2024-10-13
