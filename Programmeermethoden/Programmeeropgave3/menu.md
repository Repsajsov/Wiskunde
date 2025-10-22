HOOFDMENU (niveau 1)
│
├─── [P]arameters ────────► PARAMETERS SUBMENU (niveau 2)
│
├─── p[U]zzelmenu ───────► PUZZEL SUBMENU (niveau 2)
│
├─── [T]ekenmenu ────────► TEKEN SUBMENU (niveau 2)
│                              │
│                              └─── [T]oggle ──► Toggle-mode (niveau 3)
│
└─── [S]toppen
```

**Totaal: 4 menu's + 1 speciale modus**

---

## 🎯 Menu 1: HOOFDMENU
```
═══════════════════════════════════════
     A B C D E
   ┌───────────┐
 1 │ ○ ● ○ ○ ○ │
 2 │ ● ○ ● ○ ○ │
   └───────────┘
Zetten: 5

[P]arameters | p[U]zzelmenu | [T]ekenmenu | [S]toppen
═══════════════════════════════════════
Keuze: _
```

**4 opties:**
- **P** → Parameters submenu
- **U** → pUzzelmenu
- **T** → Tekenmenu
- **S** → Stop programma

---

## ⚙️ Menu 2: PARAMETERS SUBMENU
```
═══════════════════════════════════════
HUIDIGE PARAMETERS:
  Hoogte: 5
  Breedte: 5
  Random percentage: 50%
  Aan karakter: ●
  Uit karakter: ○
  Torus: nee
  Pen: 0 (normaal)

[H]oogte | [B]reedte | [R]andom% | [A]an | [U]it | 
[T]orus | [P]en | Terug naar hoofdmenu
═══════════════════════════════════════
Keuze: _
```

### 📋 Opties in Detail

#### **H - Hoogte**
```
Nieuwe hoogte (1-20): 7
```
- Input: getal 1-20
- Functie: `leesGetal(20)`

#### **B - Breedte**
```
Nieuwe breedte (1-20): 10
```
- Input: getal 1-20
- Functie: `leesGetal(20)`

#### **R - Random percentage**
```
Percentage lampen aan bij Random (0-100): 60
```
- Input: getal 0-100
- Functie: `leesGetal(100)`
- Gebruikt bij Random optie in Tekenmenu

#### **A - Aan karakter**
```
Karakter voor lamp AAN: ●
```
- Input: 1 karakter
- Functie: `leesOptie()` of `cin.get()`
- Display op bord

#### **U - Uit karakter**
```
Karakter voor lamp UIT: ○
```
- Input: 1 karakter
- Functie: `leesOptie()` of `cin.get()`
- Display op bord

#### **T - Torus**
```
Torus modus? (j/n): j
```
- Input: j of n
- Functie: `leesOptie()`
- **Torus = fietsband:**
  - Boven van bord verbonden met onder
  - Links verbonden met rechts
  - Bij klik: buren "wrappen around"
  
**Voorbeeld zonder torus:**
```
   A B C
 1 ○ ○ ○
 2 ○ ○ ○
```
Klik A1 → alleen A1, B1, A2 (geen wrap)

**Met torus:**
```
Klik A1 → A1, B1, A2, C1 (wrap links), 2C (wrap boven)
```

#### **P - Pen**
```
Pen modus (0/1/2): 1
```
- Input: 0, 1, of 2
- Functie: `leesGetal(2)`

**Pen modes:**
- **0** = normaal (alleen cursor beweegt)
- **1** = aan-pen (bij bewegen → lamp gaat AAN)
- **2** = uit-pen (bij bewegen → lamp gaat UIT)

**Gebruikt in Toggle-mode!**

#### **Terug**
- Terug naar hoofdmenu

---

## 🧩 Menu 3: pUZZELMENU
```
═══════════════════════════════════════
     A B C D E
   ┌───────────┐
 1 │ ○ ● ○ ● ○ │
 2 │ ● ● ● ○ ○ │
 3 │ ○ ● ○ ○ ○ │
   └───────────┘
Zetten: 0

[V]olg | [L]os 5×5 | [S]peel oplossing | [D]oe zet | Terug
═══════════════════════════════════════
Keuze: _
```

**5 opties:**

### **V - Volg**
Automatisch oplossen rij voor rij (behalve onderste)

### **L - Los 5×5**  
Los onderste rij op (alleen voor 5×5 bord)

### **S - Speel oplossing**
Speelt opgeslagen oplossing af

### **D - Doe zet**
```
Welke zet (bijv A1, B2): B3
```
- Input: schaaknotatie
- Lamp + buren flippen
- Teller++
- Opslaan in oplossing

### **Terug**
Naar hoofdmenu

---

## 🎨 Menu 4: TEKENMENU
```
═══════════════════════════════════════
     A B C D E
   ┌───────────┐
 1 │ ○ ○ ○ ○ ○ │
 2 │ ○ ○ ○ ○ ○ │
   └───────────┘

[S]choon | [R]andom | [T]oggle | [G]enereer | Terug
═══════════════════════════════════════
Keuze: _
```

**5 opties:**

### **S - Schoon**
- Alle lampen uit
- Reset oplossing

### **R - Random**
- Eerst schoon
- Dan random lampen aan (volgens percentage parameter)

### **T - Toggle**
Start Toggle-mode (zie hieronder) ⬇️

### **G - Genereer**
```
Moeilijkheidsgraad (aantal zetten): 5
```
- Input: getal
- Start met schoon bord
- Doe random g zetten
- Onthoud zetten in oplossing

### **Terug**
Naar hoofdmenu

---

## 🎮 Toggle-mode (niveau 3)
```
═══════════════════════════════════════
     A B C D E
   ┌───────────┐
 1 │[○]○ ○ ○ ○ │  ◄── cursor zichtbaar
 2 │ ○ ● ○ ○ ○ │
   └───────────┘

W=omhoog | A=links | S=omlaag | D=rechts | 
T=toggle lamp | Q=klaar
═══════════════════════════════════════
```

**Acties:**
- **W** → beweeg omhoog (+ pen actie)
- **A** → beweeg links (+ pen actie)
- **S** → beweeg omlaag (+ pen actie)
- **D** → beweeg rechts (+ pen actie)
- **T** → flip 1 lamp (alleen die lamp, geen buren!)
- **Q** → terug naar Tekenmenu

**Met Pen:**
- Pen=0: alleen bewegen
- Pen=1: bewegen + lamp AAN zetten
- Pen=2: bewegen + lamp UIT zetten

---

## 📊 Samenvatting

| Menu | Niveau | Opties | Terug naar |
|------|--------|--------|------------|
| Hoofdmenu | 1 | 4 | (stop programma) |
| Parameters | 2 | 7+terug | Hoofdmenu |
| pUzzelmenu | 2 | 4+terug | Hoofdmenu |
| Tekenmenu | 2 | 4+terug | Hoofdmenu |
| Toggle-mode | 3 | 6+quit | Tekenmenu |

**Totaal: 4 menu's + 1 modus** ✅

---

## 🎯 Navigatie Flow
```
START
  ↓
HOOFDMENU
  ├─ P → PARAMETERS → terug → HOOFDMENU
  ├─ U → PUZZELMENU → terug → HOOFDMENU
  ├─ T → TEKENMENU ─┬─ terug → HOOFDMENU
  │                 └─ T → TOGGLE-MODE → Q → TEKENMENU
  └─ S → STOP