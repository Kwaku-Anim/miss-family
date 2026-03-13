/**
 * MISS-AFIA: Microstrain Intelligence Sensing System
 * Fully Embedded Vision-Based Displacement Measurement
 * 
 * Hardware: ESP32-CAM (AI Thinker)
 * Resolution: 10μm validated against LVDT
 * Cost: $65 total (97% reduction vs conventional systems)
 * 
 * Author: Kwaku Anim Asare
 * Institution: Dalian University of Technology
 * License: MIT
 */

#include <Arduino.h>
#include <esp_camera.h>
#include <WiFi.h>
#include "vision.h"

// Camera pin definitions for AI Thinker ESP32-CAM
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// System configuration
const float PIXEL_SIZE = 2.8e-6;  // 2.8 μm pixel pitch
const float LENS_MAG = 0.5;       // Lens magnification
const int ROI_SIZE = 64;          // Region of interest size
const float CONFIDENCE_THRESHOLD = 0.85;

// Global variables
camera_config_t config;
ZNCC_Tracker tracker;
float displacement_um = 0.0;
unsigned long lastCapture = 0;
const unsigned long CAPTURE_INTERVAL = 100; // 10 Hz

void setupCamera() {
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_GRAYSCALE;
    config.frame_size = FRAMESIZE_QVGA;  // 320x240
    config.jpeg_quality = 12;
    config.fb_count = 1;
    
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed: 0x%x\n", err);
        ESP.restart();
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("MISS-AFIA: Starting up...");
    
    setupCamera();
    tracker.initialize(ROI_SIZE);
    
    Serial.println("System ready. Monitoring displacement...");
}

void loop() {
    if (millis() - lastCapture >= CAPTURE_INTERVAL) {
        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Camera capture failed");
            return;
        }
        
        // Process frame and calculate displacement
        float zncc_confidence = tracker.processFrame(fb->buf, fb->width, fb->height);
        
        if (zncc_confidence > CONFIDENCE_THRESHOLD) {
            float pixel_disp = tracker.getDisplacement();
            displacement_um = pixel_disp * PIXEL_SIZE / LENS_MAG * 1e6;
            
            Serial.printf("Displacement: %.2f μm | Confidence: %.3f\n", 
                         displacement_um, zncc_confidence);
        } else {
            Serial.println("Low tracking confidence - reinitializing...");
            tracker.reinitialize(fb->buf, fb->width, fb->height);
        }
        
        esp_camera_fb_return(fb);
        lastCapture = millis();
    }
}
