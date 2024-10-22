<img src="/assets/images/butler.jpg" width="80%" height="80%" />
 
# Slow Website

> Why This Website May Be Loading Slow For You, And What You Can Do To Boost Your Internet 

Even though we operate a modern website backed by state-of-the-art *Content Delivery Networks* (*CDN*) and *static HTML*, while most users around the globe experience a *lightning-fast website*, customers of some *ISPs* (*Internet Service Providers*) may encounter painstakingly slow load times. German customers of *Deutsche Telekom* (and its affiliates) are among those affected.

If you are experiencing a slow website, **read on** as this issue is **not specific to this website**. You might notice *slow downloads* and *almost unusably slow websites* with many other content providers. This is an issue with your *ISP*.

> [!NOTE]
> After resolving this issue with my *ISP* (see below), several other *maker websites* I visit regularly suddenly became *fully functional*. I had always assumed they were broken: *images* wouldn't load or took a long time to appear. Fixing the *ISP problem* made these websites load instantly.

The tricky part about this issue is that it affects *only some* websites and downloads at random. So when you run a *speed test* or visit other sites, things often work fine. The severity of the issue can also vary throughout the day or over time, which leads *ISPs* to blame individual websites for slow performance.

In this article, I'll explain the reasons behind this issue, what you can do to fix it, and show that **the problem lies with the ISP**, not with individual websites.


## Quick Summary
If your hair is on fire, here’s a quick summary of the culprit and what you can do:

Some *ISPs* (like *Deutsche Telekom* in Germany, and affiliated *ISPs*) are notorious for having *routing problems*. They direct your requests to outdated *edge servers* of *CDNs* (*Content Delivery Networks*).

*CDNs* are designed to *speed up your internet experience*: their *edge servers* act like *mirrors* in your vicinity. When *routing* is correct, your requests take just a few hops to reach the closest *CDN server* in your neighborhood.

However, affected *ISPs* route your requests to the *wrong CDN servers* in a completely different region of the world. This forces your requests to travel long distances, resulting in delays or even packet loss.

This explains the observations:

* **Only some users are affected**: They are customers of *ISPs* with bad routing. Customers of other *ISPs* are not affected.
* **Only some websites or downloads are affected**: Websites using fast *CDNs* like *Cloudflare* are affected. Websites that don’t prioritize speed or use different *CDNs* are unaffected.
* **The issue's severity may vary during the day or over time**: *Edge servers* frequently change *IP addresses* (for security reasons), so stale *ISP routing* may randomly point to the correct *CDN edge server*.

There’s nothing *you* can do to fix your *ISP’s* routing. Likewise, the *website operator* (like me) cannot resolve it. However, **you can fix the issue indirectly**:

* **Change ISP**: Switch to an *ISP* that handles *routing* correctly. This may not be easy due to ongoing contracts or infrastructure.
* **Change Routing**: Use a *VPN* like [NordVPN](https://refer-nordvpn.com/DdmJIprBMeZ). A *VPN* bypasses your *ISP’s bad routing*, resulting in a *truly fast internet experience*. Most *VPN services* offer *trial periods* or *money-back guarantees*, so you can test this solution yourself.

> [!NOTE]
> With a *VPN*, you can easily switch between your *ISP’s routing* and the *VPN*. This proves that neither *your computer* nor the *website operator* is to blame for the slowness—it's the (bad) *ISP routing*.

If you want to dive deeper and actually *see for yourself*, let’s run a couple of tests next.


## Ingredients For Fast Internet Experience
Most users focus solely on their *Internet Service Provider* (*ISP*) for *fast Internet speeds*. High monthly fees promise a supposedly fast *Internet connection*, such as *250Mbit/s* or even *1Gbit/s*. However, you might occasionally notice that your Internet speed is much slower, and **only certain** websites, downloads, or services (such as video conferences) perform sluggishly.

To understand why this happens, it’s important to know that there are **two** crucial components for fast Internet. Your *ISP connection* is just **one** of them:

* **Internet Service Provider (ISP):** This is the company that provides you with a *modem* and physically connects you to the *Internet*. *ISPs* are responsible for the **last mile**: connecting *your home or smartphone* to the rest of the *Internet*. Having a *fast ISP* gives you a fast entry into the *Internet*. However, it does not guarantee *fast transfer speeds* **within** the *Internet*.
* **Routing:** Once your data packets *enter* the *Internet* through your *ISP's access point*, they need directions to reach their destination—similar to how a GPS navigates your car. This process is called *Routing*. Good *Routing* is just as important as having a fast *ISP*. It can either send your packets to the nearest *CDN server* (good), or route them across the globe to the *original webserver* (very bad).

> [!NOTE]
> Think of it like this: a *Ferrari* (your *fast ISP*) won’t win a race against a *Fiat* (a *slower ISP*) if the *Ferrari’s* GPS (aka *Routing*) sends it on detours through rough backroads, while the *Fiat’s GPS* takes the highway and exits at the closest ramp.


### Why *This* Website May Be Slow
The funny thing is that *bad routing* doesn’t seem to affect *all websites* equally. That’s why you probably don’t notice it at first. Here’s why only *some* websites and downloads are impacted:

This website is backed by sophisticated *CDNs* (*Content Delivery Networks*) and uses *static HTML*—all the ingredients for *super fast and super responsive websites*. Routine global audits confirm that this website ranks among the top 5% for speed.

If pages still take painstakingly long to load **for you**, and if **you** notice images loading slowly line by line, missing fonts, or misaligned icons, then there are only *three* possible reasons:

* **Slow ISP/Bad Coverage:** Obviously, if you are using a *very slow ISP*, or are in an area with *poor Internet coverage*, it’s no surprise you’d experience slow Internet. In this case, though, **all websites would be slow**, not just *some*.
* **Slow Hosting Provider:** Theoretically, the website operator (that would be *me*) could have chosen a *poor* hosting provider with slow download speeds and insufficient capacity. However, in this case, **everyone** would experience a slow website, not just *some users*, and our audits would report slow performance (which they don’t).
* **Bad Routing:** If **you** experience a slow website while **others** enjoy lightning-fast speeds, then **your routing** is the problem. Your data packets are taking detours around the globe instead of the direct route, both on the way *to* the website and *back to you*. The majority of users have *correct routing*, and for them, the website is lightning fast.



## What Does Routing Do?
Without delving too much into networking, when you navigate to a website, your request is routed to the web server hosting the website, and the server returns the data so your browser can display the page.

The *Internet* uses *data packets*, which are sent from server to server, starting with those close to you, until they finally reach their destination.

*Routing* on the Internet is the process of selecting paths for data to travel from *you* to the *target* (and vice versa) across many interconnected networks. It works similarly to a *navigation system* in your car.

### Visualizing the Route
You can visualize the *hops* your data packets take using tools like `tracert.exe` on *Windows*. Below is the *route* selected for me to reach *done.land*:


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
Aside from the high number of hops, this trace doesn’t seem alarming at first. I *am* apparently reaching the fast *CDN edge servers*, so I *should* be getting a fast response. But is this really the case?

Let’s now examine how the actual website behaves.

### Debugging a Slow Website
Most modern browsers come with advanced debugging tools. In *Chrome*, press `F12` to open the Developer Tools, then click the *Network* tab and clear the list of network requests.

To ensure you're measuring real download times (and not cached elements from your browser memory), clear your browser cache before testing. In *Chrome*, click the *three-dot* menu, then choose *Delete browsing data...*. It’s enough to delete the last *24 hours* of cached data.

#### Navigate to the Webpage Under Test
Now, enter the *URL* of the website you want to test. I chose a random [*done.land* article](https://done.land/components/microcontroller/families/esp/esp32/lilygot-display/t-display) containing multiple images and other resources. You can now watch the browser download all the webpage data, with each resource showing its URL, size, and the time it took to download:

<img src="images/routing_slow_website_chrome_debug_error.png" width="100%" height="100%" />

In this example, downloading the entire webpage took an absurd *10.4 **minutes***. During that time, only *1.8MB* of data was transferred—an average of *2800 bytes per second* on a *wired 250Mbit/s ISP* connection.

Even worse, the download wasn’t successful: one image failed to load, causing a timeout error: `ERR_QUIC_PROTOCOL_ERROR`.

Clearly, something is seriously wrong. My *ISP* routed my packets to the correct *CDN*, but targeted the *wrong* *CDN edge server*.

The *IP addresses* of the *edge servers* (the entry points to the *CDN*) are *dynamic* and frequently change for security and infrastructure reasons. While I may be wrong, it seems my *ISP* isn’t using the correct *IP addresses* for my location. We’ll dive deeper into this in a moment.

Regardless of the *why* or *how*, the website **is definitely impaired**, and the **cause is bad routing**.


### Border Gateway Protocol
*Routing* is complex and involves many components. Your *ISP* is responsible for the *Border Gateway Protocol* (*BGP*), which is used to exchange routing information between large networks, or "autonomous systems" (*AS*), such as *ISPs* (*Internet Service Providers*), major players (like *AWS*), and crucially, *CDNs* (such as *Cloudflare*).

For many years, some *ISPs*, like *Deutsche Telekom* in *Germany*, seem to have struggled with poor *Peering Agreements* or outdated routing information. *ISPs* enter into peering agreements with one another to exchange traffic. When these agreements are poorly managed or costly for certain routes, the *ISP* might route traffic through less optimal or **outdated** paths, significantly affecting speed.

There are [numerous discussions in German forums](https://telekomhilft.telekom.de/t5/Festnetz-Internet/Unglaublich-schlechtes-Routing/td-p/6827554) highlighting this issue.

> [!IMPORTANT]
> If you are experiencing slow *done.land* web pages, remember that this is just a *symptom* of a larger issue. The challenge is that only specific networks and content delivery systems are impacted. Even if you're not particularly concerned with *this site*, addressing the problem could significantly enhance your *Internet experience* overall—and you may be surprised at how much faster your downloads become.


## Solving the Issue
Since the fundamental *routing problem* is caused by how your *ISP* directs the data (and seems to ignore fast *CDNs*), you have two options:

* **Change ISP:** Switch to a new *ISP*. This may be complex and time-consuming due to contracts, infrastructure, and the need to ensure that your *new ISP* isn’t reliant on the same critical infrastructure as your *old ISP*.
* **Use VPN:** The simplest solution is to use a *VPN* (*Virtual Private Network*). Essentially, you bypass your *ISP's routing* in favor of the *VPN’s* routing.

### Using VPN
When you use a *VPN*, you still rely on your *ISP* for the *last mile*. However, from there, your data packets access the nearest and fastest *VPN server* in your region.

Your data then travels **anonymously** within the *VPN* server network. *VPNs* optimize routing for better speed and protect your *privacy* by anonymizing your *IP address*. That’s why *VPNs* are banned in most dictatorships (though not in *Europe* or the *US*).

The downside is that *VPNs* are an additional *paid service* on top of your existing *ISP*. However, as mentioned, fast and safe Internet consists of two components: a *fast last mile* (provided by your *ISP*) and optimized *routing* (often lacking from your *ISP*, but provided by a *VPN*).

> [!NOTE]
> Your *ISP* may already offer fast, intelligent *routing*. Even so, using a *VPN* gives you extra control and could still make sense for added *security* and *privacy*.

As a *Deutsche Telekom* customer in *Germany*, I was **heavily** affected by speed issues, so adding a *VPN* was an easy decision, with the additional *privacy* being a nice bonus. After comparing options, I went with the basic (cheapest) [NordVPN package](https://refer-nordvpn.com/DdmJIprBMeZ), getting a *2-year contract* for around €90 (paid out of pocket, no affiliation). With its *30-day money-back guarantee*, you can try it out to see if it resolves your speed issues.

> By using this [NordVPN link](https://refer-nordvpn.com/DdmJIprBMeZ), *you and I* will both get a few extra free months.

After testing, *NordVPN* fixed all my issues and more. Previously, I noticed certain websites and downloads performed worse than others. With *NordVPN*, all my Internet resources now load consistently fast, finally letting my *expensive, superfast ISP* deliver on its promises.

> [!IMPORTANT]
> While connected to a *VPN*, your browser communicates with the virtual network. This means it cannot resolve local *mDNS* names like `homeassistant.local:8123`. To access local devices, either *disconnect* from the *VPN* or use the device’s local *IP address* instead of its *mDNS name*.



## Walkthrough: NordVPN
If you're curious about how a *VPN* works and how to set it up, here’s a quick walkthrough of my initial steps with [NordVPN](https://refer-nordvpn.com/DdmJIprBMeZ).

### Download NordVPN App
Your journey begins with downloading the [NordVPN app](https://nordvpn.com/download/). It’s available for *Windows*, other operating systems, and smartphones.

<img src="images/nordvpn_1.png" width="50%" height="50%" />

After installing the software, you’ll find links on your *Desktop* and in your *Start Menu* (or an *app icon* on your smartphone). When you launch the *NordVPN* app, you can either *log in* or [create a NordVPN account (sign up)](https://refer-nordvpn.com/DdmJIprBMeZ). There are various *paid plans*, but no *free tier*.

If you don’t have a *NordVPN* account yet, consider using [this link to sign up](https://refer-nordvpn.com/DdmJIprBMeZ), which gives *you and me* a few extra free months.

When you click *Log in*, your browser will open and prompt you for your *username* and *password*. After completing the browser-based authentication, you’ll return to the *NordVPN app*.

### Select VPN Server
The *NordVPN app* displays your connection status:

* **Not Connected:** **red** *Not Connected* indicates you’re using your *ISP’s* routing, and you can see your currently assigned *IP address*. In this mode, you can access local *mDNS* addresses as usual (i.e., `homeassistant.local:8123`).
* **Connected:** **green** *Connected* signifies that you’re using the *VPN* and its routing. Your *ISP name* will no longer be the one connecting your home to the Internet, and you’ll be using anonymized *IP addresses*. In this mode, you cannot access local *mDNS* addresses from your browser unless you replace the *mDNS* name with the device's *IP address* (i.e., `http://192.168.68.123:8123`).

You can connect through numerous servers located worldwide. To maximize speed, choose a *VPN server* as close as possible to your current location.

*Recent connections* (the top list) are your *favorites*. Initially, this list is randomly filled, so do not use *Quick Connect* or one of the servers in the top list.

<img src="images/nordvpn_3.png" width="100%" height="100%" />

Instead, in the *lower list*, select the country where you are located. This action adds the country to your *upper list* (your favorites), allowing you to easily connect to a server in that country in the future.

To actually *connect* and start using the VPN, click the country in your top list.

> [!TIP]
> Clicking the *three-dot menu* to the right of the selected country in the **lower** list reveals the available *cities* in that country. By default, *NordVPN* automatically selects the city with the fastest connection to you.

Once connected, you’ll see your *country flag* and the currently active *ISP* at the top left of your window.



<img src="images/nordvpn_4.png" width="30%" height="30%" />

## Results of fix
To observe the effects of using *NordVPN*, let's repeat the website tests with the *VPN* active. Here’s what the route now looks like:

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
This target IP address is *still* registered to *Cloudflare*, located in *San Francisco*. However, the *registration data* is **not necessarily identical to where the actual server is located**.

One hop before reaching the target, the trace reveals that we are hopping through `ipv4.de-cix.ham.de.as13335.cloudflare.com`, which is located in *Hamburg, Germany*, just around the corner from my location:

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
In a nutshell, *VPN routing* has directed my data packets straight to the *closest available CDN server*, just a few kilometers from my home. The hops in between (*185.161.202.2* and *185.161.202.3*) were also located right in *Hamburg*:

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
Keep in mind: before using *VPN*, my *ISP* had routed my packets all the way across the Atlantic Ocean, serving the website from a different continent with frequent total *packet losses*, resulting in extremely low speeds.

Let's verify the trace information and look at the *real-world consequences* of this new routing. I'll repeat the website test in my *Chrome* browser (don’t forget to clear the browser cache before you test again). Remember: last time, it took over **10 minutes** to fully load the web page.

![VPN Testing Result](images/routing_slow_website_chrome_debug_vpn.png)

This time, the same web page appeared instantly. After just *1.12 seconds*, the complete web page, along with all its images and fonts, loaded, transferring *2.7MB* of data. The transfer rate was *2.4 MByte/s* (compared to the previous 2.8KB/s), making it almost *1000 times* faster.


> Tags: Website, Slow, VPN, ISP, Routing, Cloudflare, NordVPN, Peering Agreement, Border Gateway Protocol, BGP, Telekom

[Visit Page on Website](https://done.land/tools/internet?015434101113241156) - created 2024-10-12 - last edited 2024-10-20
