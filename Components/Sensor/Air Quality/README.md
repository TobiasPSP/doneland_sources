<img src="/assets/images/air1.png" width="100%" height="100%" />
 
# Air Quality Sensors

> Measuring CO2 And Other Toxic Gases

*Air Quality Sensors* measures various parameters within the air, including *particulate matter* (*PM*), *volatile organic compounds* (*VOCs*), *carbon dioxide* (*CO2*), *carbon monoxide* (*CO*), *ozone* (*O3*), *nitrogen dioxide* (*NO2*), and other pollutants. 

> [!TIP]
> Often, sensors also measure *temperature* and *humidity* to *compensate* their readings. 

They provide real-time data on air pollution levels, helping to assess the overall air quality and potential health risks.

> [!NOTE]
> Not *all* sensors measure *all* parameters, and it depends on sensor type and architecture *how accurately* the parameters are detected.



## Determining Air Quality
In normal environments, the most important sensor parameters for determining average air quality typically include:

1. **Particulate Matter (PM)**: PM2.5 and PM10 are important indicators of airborne particles, including dust, pollen, smoke, and other pollutants. High levels of PM can lead to respiratory issues and reduced visibility. Public *PM sensors* in your proximity are [available on a map](https://sensor.community/en/) and can also be integrated in your personal instance of *Home Assistant*, or you can setup your own *PM sensor*.

2. **Carbon Dioxide (CO2)**: CO2 levels are indicative of indoor air quality and ventilation. Elevated CO2 levels can indicate poor ventilation or the presence of occupants, which may lead to discomfort and reduced cognitive function. *NDIS* sensors like the *SCD30* measure specifically *CO2* while cheaper *MOS* sensors measure unspecific physical effects that can only *approximate* CO2 concentrations.

3. **Volatile Organic Compounds (VOCs)**: VOCs are emitted from various sources such as paints, solvents, cleaning products, and building materials. Monitoring VOC levels is crucial for assessing indoor air quality and potential health risks.

4. **Carbon Monoxide (CO)**: CO is a colorless, odorless gas produced by incomplete combustion of fuels such as gas, oil, and wood. High levels of CO can be deadly and are a major concern in indoor environments.

5. **Ozone (O3)**: Ozone is a reactive gas formed by the interaction of sunlight with pollutants such as nitrogen oxides (NOx) and volatile organic compounds (VOCs). While ozone at ground level can be harmful to health, it is typically less of a concern in normal indoor environments.

6. **Temperature and Humidity**: Monitoring temperature and humidity levels is important for comfort and can also affect the dispersion and concentration of airborne pollutants.

These parameters collectively provide insights into the overall air quality, indoor comfort, and potential health risks in normal environments.

### CO2 Levels
The CO2 concentration in the air is a good estimate for *air quality*. Specific CO2 NDIS sensors accurately measure the CO2 concentration in *ppm* (*parts per million*), which in turn allows conclusions on air quality:

| ppm | Symptoms | Air Quality |
| --- | --- | --- |
| 250-400 | none | background concentration in fresh outdoor ambient air |
| 400-1.000 | none |occupied indoor spaces with good air exchange |
| 1.000-2.000 | Complaints of *drowsiness* | poor air |
| 2.000-5.000 | *Headaches*, *sleepiness*, *loss of attention*, *poor concentration*, *increased heart rate* | stagnant, stale, stuffy air |
| >5.000 | *unability to perform work* | enclosed non-ventilated spaces (i.e. silos) workplace exposure limit in most jurisdictions |
| >40.000 | *permanent brain damage*, *coma*, *death*  | serious oxygen deprevation |

## Measuring Air Quality
There are *specific* and *unspecific* approaches to measuring air quality data, varying in *complexity* (thus *cost*), and *accuracy*.

### Cheap MOS Sensors
*Solid-state metal-oxide semiconductor* (*MOS*) sensors are simple and cheap: they detect changes in electrical conductivity when exposed to gases *like* CO2 and many others. **Such sensors are *unspecific* and cannot measure a *single* parameter:

* **Unspecific:** they measure a *combination* of parameters, and one parameter (i.e. *CO2*) may be influenced by another (i.e. *organic substances*). That's why the provide only an *overall estimate* 
* **Temperature and Humidity:** *MOS sensors* are substantially affected by *temperature* and *humidity*. Their sensor readings may overshoot with *high humidity*, and they may not work at all with *extremely low humidity*.

Because of this, *MOS sensors* are generally used to provide *overall air quality alarms* in controlled environments without extreme conditions for *temperature* and *humidity*. If you like a *MOS sensor* to *focus on a particular substance* (i.e. *CO2*), you need to know which *other substances* can influence the sensor, and exclude these.

> [!TIP]
> I noticed that *MOS sensors* do **not** correlate well with air quality in *conference rooms* or a *lab*. While *NDIR sensor readings* could very well be correlated to *human presence* and the *subjective feeling of good and bad air quality*, *cheap MOS sensor readings* were not suitable to trigger *air quality warnings*. Their readings appeared somewhat *random* and may have been influenced by many other factors. 

> [!IMPORTANT]
> *MOS sensors* often need a *burn-in time* of *24 hours* or more before producing accurate results. You may want to connect your sensors to a power supply and leave them powered on for a day before using them.


### Expensive NDIR Sensors
*Non-Dispersive Infrared* (*NDIR*) sensors measure the concentration of substances by detecting its absorption of infrared radiation at specific wavelengths. In contrast to *MOS* sensors, *NDIR* sensors *specifically measure the substance* they were designed for and are known for their *reliability* and *accuracy*. *NDIR sensors* are widely used in *high quality indoor air quality monitors*.

*NDIR* is based on *infrared absorption effects*, so *NDIR sensors* are calibrated for a *specific substance* - make sure you pick the *NDIR sensor* for the substance you are after. *NDIR* can only be used to measure substances that in fact *absorb infrared light*. 

Since *NDIR* sensors are technically much more complex, they are also significantly more expensive than *MOS sensors*.

> [!TIP]
> When you purchase *air quality monitoring devices* off the shelf, the sensor type used is often not disclosed. Since *NDIR* sensors by themselves cost around €20 (and even in bulk at least €10), it is safe to assume that *cheap air quality monitors* typically use simple *MOS sensors* and allow just *rough guesses* about *air quality*.





### Other Sensor Types
There are many other sensor types for *scientific* and *industrial* use with increased *accuracy*. For normal home use cases, their cost outweighs any potential benefit.

Such sensors involve *Chemical Absorption using chemical reagents*, *gas chromatography*, *photoacoustic spectroscopy* (*PAS*), and *Tunable Diode Laser Absorption Spectroscopy* (*TDLAS*). They are not discussed here.

> Tags: CO2, MOS, NDIS, TDLAS, PAS

[Visit Page on Website](https://done.land/components/sensor/airquality?671751061105240606) - created 2024-06-04 - last edited 2024-07-16
