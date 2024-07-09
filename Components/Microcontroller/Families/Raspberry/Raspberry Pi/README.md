<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Raspberry Pi

> Powerful Single-Board Computer Running Various Operating Systems

*Raspberry Pi* is a *computer* that typically runs a *Debian*-based *Linux* distribution but can run basically *any* operating system, including specialized versions (like *Home Assistant OS*). A graphical user interface can be included.

## Why Not Use Windows Or Apple?

*Windows* and *Mac* computers run perfect *general purpose consumer* operating systems that are simple to use, and most of us own at least one. 

For *specialized* use cases, these computers and their operating systems are much too complex, heavy, and limiting. 

With *Raspberries*, you have all the (technical) freedoms to implement just about anything you want. Consumer operating systems are locked down so consumers do not shoot themselves in the foot.


> [!NOTE]
>*Raspberry Pis* are not designed to *compete against* or *replace* conventional *PCs*. They are just efficient and flexible computers for lab and scientific/engineering projects.

Here are the benefits of using a *Raspberry Pi*:

* **Powerful:** the latest *Raspberryx Pi 5* with 8GB RAM may not outperform the latest Intel or iMac hardware but provides excessive computational power for even the most demanding *dedicated technical* tasks. At the same time, it uses extremely little energy and can run continuously as a server without busting the bank on energy bills.
* **Dedicated:** it can use a wide variety of *storage media* that are easily switchable. While the primary operating system is best installed on a *SSD drive* (although not required), simple *SD Cards* can be used as alternate boot media to set up temporary environments or tool chains and boot from these on demand.
* **Fast:** depending on the set up, a *Raspberry Pi* starts in seconds and reboots in a snap.
* **Small and Quiet:** its form factor is very small and runs noiseless. Although a fan-based active cooler is recommended, the fan doesn't run very often as the *Raspberry Pi 5* isn't easily pushed to its limits.
* **Flexible:** *Raspberry Imager* is a tool that runs on your *classic* PC and lets you easily select the operating system and environment you need. It can apply your initial configuration (passwords, WiFi access, language settings, etc) and write it as an *image* to your storage medium. A *Raspberry Pi* then directly boots into this environment without any complex setup.

In a nutshell, although a *Raspberry Pi 5* isn't always as computationally powerful as the latest *Windows* or *Mac* computer, it often still outperforms them: 

* Since your environments and operating system setups can be tailored to exactly meet your needs, the *Raspberry Pi* can focus all of its capabilities on just your requirements. It does not need to waste power on *consumer bling* and *default features* that you don't actually need and never asked for.
* Less unneeded work requires less energy and produces less noise and heat.
* Less unwanted features lower the security risks as they limit attack surfaces.



### Thin Client PCs
Recently, it became a trend to use refurbished *Thin Client PCs* as servers and put the free [Proxmox](https://www.proxmox.com/en/) virtualization software on them.

This works very similar to a *Raspberry Pi* which also is a *host* and runs some *operating system* on a storage medium. 

With a *thin client* and *Proxmox*, you can run *multiple* operating systems and use *multiple* server environments at the same time.

Unless you really need this, using a *thin client* puts the original concept behind *Raspberry Pis* upside down: their whole idea is *simplicity* and *energy-efficiency*. 

With *thin clients*, here is what you really get:

* **Wasting Energy:** Most *thin client PCs* require significantly more power that a *Raspberry Pi*. That is ok provided *you really need their power*. Running *Home Assistant* continuously 7/365 *does not require this power*, and the power bill will become a considerable part of *TOC* (*total cost of ownership*).
* **Complex:** forums are filled with threads about fixing problems that did not exist in the first place when using a *Raspberry Pi*. Configuring *Proxmox* and setting up virtualizations, plus running systems in unsupported or non-official configurations adds many layers of unwanted complexity.
* **Unnecessary:** The majority of users requires *one* continuously running server, at most *two*. Specialized tool chains, i.e. to run *Cloud Cutter*, are required only *temporarily* and can be easily set up and run off an *SD card*.

There may be users that really benefit from running a virtualization server because they need to run more than two servers all the time.

All other reasons for using *thin clients* and *Proxmox* over *Raspberry Pi 5* are not solid: neither is it *cheaper* (especially when adding energy cost), nor *faster* (*Raspberry Pi 5* idle most of the time anyway for what they need to do), and certainly not *easier to use*.

> [!TIP]
> I am using one dedicated *Raspberry Pi 5* for *Home Assistant*, and another one as a *general pürpose tool*. The latter runs *Raspberry Pi OS*, and I am booting from various *SD Cards* whenever I need specialized tool chains. The overall hardware cost of both *Raspberries* is comparable to buying a used *Thin client* and refurbishing it, and with every new electricity bill, this changes more in favor of *Raspberries*.


## Generations

*Raspberry Pi* was released *2012* and targeted primarily towards *educational use*. It soon was adopted by the community for *robotics*, *automation*, and many other use cases requiring a backend *server* with sufficient performance.

| Version  | Processor | Remarks |
| --- | --- | --- |
| 1 | 700MHz 32-bit Single-Core ARM11 | **Raspberry Pi Model B** in 2012: The simpler and cheaper **Raspberry Pi Model A** followed later the same year. An improved **Raspberry Pi Model B+** was released in 2014.  |
| 2 | 900MHz 32-bit Quad-Core ARM Cortex-A7 |  **Raspberry Pi 2 B** in 2015: featured a 900MHz 32-bit processor and came with *1GB* RAM. **Revision 1.2** switched to a *64-bit A53* processor that would continued to be used in version *3*. It was clocked at *900MHz*. |
| 3 | 1.2GHz 64-bit Quad-Core ARM Cortex-A53 | **Raspberry Pi 3 Model B** in 2016: changed clock speed from *900MHz* to *1.2GHz*, added *802.11ac WiFi* and *USB-Boot* capabilities. In *2018*, **Raspberry Pi 3 Model B+** surfaced: clock speed was raised to *1.4GHz*, *Ethernet* speed was tripled to *300Mbit/s*, dual-band 100 Mbit/s *WiFi* was added. This was followed by **Raspberry Pi 3 Model A+** with similar enhancements. |
| 4 | 1.5GHz 64-bit ARM Cortex-A72 | **Raspberry Pi 4 Model A/B** in 2019: it added *Bluetooth 5.0*, throughput-unlimited full *Gigabit Ethernet*, two *USB 2.0 ports*, two *USB 3.0 ports*, from *1 to 8 GB RAM*, *dual-monitor support* via *Micro HDMI (Type D)* ports with *4K Resolution*, plus *USB-C power supply*. **Raspberry Pi 400** was added in 2020 as a *keyboard computer*: a *Raspberry Pi 4* with *4GB RAM* and a *1.8 GHz clock* was integrated into a *keyboard housing*. |
| 5 | 2.4GHz 64-bit ARM Cortex-A76 | [Raspberry Pi 5](materials/raspberry_pi_5_brief.pdf) in 2023: *4* or *8GB RAM*, *VideoCore VII GPU*, supporting *Vulkan 1.1*, for better performance (graphics-intensive tasks, 4K video playback), four *USB 3.0 ports*, *Bluetooth 5.2*, *802.11ax WiFi 6*, faster *MicroSD card slot*, better *USB boot capabilities*, can be powered via *USB C*, *Power over Ethernet* (*PoE*), improved power efficiency, *real-time clock* (*RTC*) |

> [!TIP]
> If you own an older model, there is typically no need to immediately upgrade. Given the significant performance boost found in *Raspberry Pi 5* and marginal *price differences*, I would not recommend to buy an older model. *Raspberry Pi 5* is *future proof* with guaranteed support until *2036*.











### Assembly Required
Typically, *Raspberry Pi* is sold either as *bare board* or as *starter kits* (containing all required parts such as *housing*, *fan*, etc.).

While there are vendors offering *pre-assembled devices* that are *ready to run*, this is a niche market.

Assembling a *Raspberry Pi* is part of the intended *educational aspect* and does not require much special knowledge. A typical assembly takes a *screwdriver* and *10 minutes of time*.



> Tags: Raspberry Pi, Versions, ARM, ARM11, ARM Cortex-A7, ARM Cortex-A53, ARM Cortex-A72, ARM Cortex-A76

[Visit Page on Website](https://done.land/components/microcontroller/families/raspberry/raspberrypi?418279061603242831) - created 2024-06-02 - last edited 2024-07-09
