<img src="/assets/images/air1.png" width="100%" height="100%" />
 
# Air Quality Sensors

> Measuring CO2 And Toxic Gases

*Air Quality Sensors* measures various parameters within the air, including *particulate matter* (*PM*), *volatile organic compounds* (*VOCs*), *carbon dioxide* (*CO2*), *carbon monoxide* (*CO*), *ozone* (*O3*), *nitrogen dioxide* (*NO2*), and other pollutants. 

Often, such sensors also measure *temperature* and *humidity*.

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

## CO2 Levels
The CO2 concentration in the air is a good estimate for *air quality*. Specific CO2 NDIS sensors accurately measure the CO2 concentration in *ppm* (*parts per million*), which in turn allows conclusions on air quality:

| ppm | Symptoms | Air Quality |
| --- | --- | --- |
| 250-400 | none | background concentration in fresh outdoor ambient air |
| 400-1.000 | none |occupied indoor spaces with good air exchange |
| 1.000-2.000 | Complaints of *drowsiness* | poor air |
| 2.000-5.000 | *Headaches*, *sleepiness*, *loss of attention*, *poor concentration*, *increased heart rate* | stagnant, stale, stuffy air |
| >5.000 | *unability to perform work* | enclosed non-ventilated spaces (i.e. silos) workplace exposure limit in most jurisdictions |
| >40.000 | *permanent brain damage*, *coma*, *death*  | serious oxygen deprevation |

## Measuring CO2
There are *specific* and *unspecific* approaches to measuring CO2, varying in *complexity* (thus *cost*), and *accuracy*.

### Cheap MOS Sensors
*Solid-state* *metal-oxide semiconductor* (*MOS*) sensors sensors are cheapest. They detect changes in electrical conductivity when exposed to gases *like* CO2 (many other gases also influence the readings). **They do not provide a *specific* CO2 ppm value.**

MOS sensors only measure *generic changes in conductivity* rather than *directly detecting CO2* molecules: their results are affected by other gases or environmental factors like temperature and humidity. You need to *calibrate* such sensors in *fresh air* and then get an *estimate* for the overall *air quality* compared to the *fresh air* that you used for calibration.

This may well be sufficient to get a *low-cost air quality overview*.


### Expensive NDIS Sensors
*Non-Dispersive Infrared* (*NDIR*) sensors measure the concentration of CO2 by detecting its absorption of infrared radiation at specific wavelengths. In contrast to *MOS* sensors, *NDIS* sensors *specifically measure CO2* and are known for their *reliability* and *accuracy*.

*NDIS sensors* are widely used in *high quality indoor air quality monitors*.

Since NDIS sensors are much more complex, they are also much more expensive than MOS sensors and start at around 20 Euro.

> [!TIP]
> When you purchase *air quality monitoring devices* off the shelf, the used sensor type is often not disclosed. Since *NDIS* sensors alone cost at least 20 EUR, it is safe to assume that *cheap air quality monitors* use simple MOS sensors and allow just *rough guesses* about the *air quality*.





### Other Sensors
There are many other sensor types for *scientific* and *industrial* use. Their increased *accuracy* is irrelevant for normal use cases, and their prices are prohibitive.

Such sensors involve *Chemical Absorption using chemical reagents*, *gas chromatography*, *photoacoustic spectroscopy* (*PAS*), and *Tunable Diode Laser Absorption Spectroscopy* (*TDLAS*).

> Tags: CO2, MOS, NDIS, TDLAS, PAS

[Visit Page on Website](https://done.land/components/sensor/airquality?671751061105240606) - created 2024-06-04 - last edited 2024-06-04
