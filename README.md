# Grbl-plotter
 
## Typescript

### Install typescript

```bash
> npm install -g typescript

> tsc -watch *.ts (?)
```

For the latest stable version:

```bash
npm install -D typescript
```

For our nightly builds:

```bash
npm install -D typescript@next
```

### Run and watch typescript

```bash
npm install --save-dev ts-node-dev
```

### The package.json:

```json
{
  [...]

  "scripts": {
    "start": "tsc && node dist/main.js",
    "watch-and-run": "ts-node-dev --respawn -- src/main.ts"
  }

  [...]
}
```