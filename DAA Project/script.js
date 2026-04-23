let arr = [], target = 0, low = 0, high = 0, stepNum = 0, done = false, autoTimer = null;

function parseArray() {
  return document.getElementById('array-input').value
    .split(',').map(s => parseInt(s.trim())).filter(n => !isNaN(n));
}

function initSearch() {
  clearAuto();
  arr = parseArray();
  target = parseInt(document.getElementById('target-input').value);

  if (arr.length === 0 || isNaN(target)) {
    alert('Please enter a valid sorted array and target.');
    return;
  }

  arr.sort((a, b) => a - b);
  document.getElementById('array-input').value = arr.join(', ');

  low = 0;
  high = arr.length - 1;
  stepNum = 0;
  done = false;

  document.getElementById('cmp-count').textContent = '0';
  document.getElementById('max-steps').textContent = Math.ceil(Math.log2(arr.length));
  document.getElementById('result-banner').className = 'hidden rounded-2xl p-4 text-center font-bold text-lg mono';
  document.getElementById('step-log').innerHTML =
    `<p class="mono text-sm" style="color:var(--muted)">Array loaded. Target = <span style="color:var(--mid)">${target}</span>. Press <strong>Next Step</strong>.</p>`;

  document.getElementById('btn-next').disabled = false;
  document.getElementById('btn-auto').disabled = false;

  renderArray();
}

function renderArray(midIdx = -1, foundIdx = -1) {
  const container = document.getElementById('array-visual');
  container.innerHTML = '';

  arr.forEach((val, i) => {
    const wrapper = document.createElement('div');
    wrapper.className = 'array-box flex flex-col items-center';
    wrapper.style.minWidth = '48px';

    // Pointer labels
    const labels = [];
    if (i === low && !done)           labels.push({ text: 'L', color: 'var(--low)'   });
    if (i === midIdx && !done)        labels.push({ text: 'M', color: 'var(--mid)'   });
    if (i === high && !done)          labels.push({ text: 'H', color: 'var(--high)'  });
    if (foundIdx >= 0 && i === foundIdx) labels.push({ text: '✓', color: 'var(--found)' });

    const labelRow = document.createElement('div');
    labelRow.style.cssText = 'height:24px; width:100%; display:flex; justify-content:center; gap:3px; align-items:flex-end;';
    labels.forEach(l => {
      const span = document.createElement('span');
      span.className = 'pointer-label';
      span.style.cssText = `background:${l.color}22; color:${l.color}; border:1px solid ${l.color};`;
      span.textContent = l.text;
      labelRow.appendChild(span);
    });
    wrapper.appendChild(labelRow);

    // Box
    const box = document.createElement('div');
    box.className = 'mono text-sm font-bold flex items-center justify-center rounded-lg border';
    box.style.cssText = 'width:48px; height:48px; background:var(--surface2); border-color:var(--border); color:var(--text);';
    box.textContent = val;

    if (foundIdx >= 0 && i === foundIdx) {
      box.classList.add('box-found', 'pulse-found');
    } else if (midIdx === i && !done) {
      box.classList.add('box-mid');
    } else if (!done && (i < low || i > high)) {
      box.classList.add('box-eliminated');
    } else {
      if (i === low  && !done) box.classList.add('box-low');
      if (i === high && !done) box.classList.add('box-high');
    }

    wrapper.appendChild(box);

    // Index label
    const idx = document.createElement('div');
    idx.className = 'mono mt-1';
    idx.style.cssText = 'font-size:10px; color:var(--muted);';
    idx.textContent = i;
    wrapper.appendChild(idx);

    container.appendChild(wrapper);
  });
}

function addLog(html) {
  const log = document.getElementById('step-log');
  const row = document.createElement('div');
  row.className = 'step-row mono text-xs rounded-lg px-3 py-2';
  row.style.background = 'var(--surface2)';
  row.innerHTML = html;
  log.appendChild(row);
  log.scrollTop = log.scrollHeight;
}

function nextStep() {
  if (done) return;

  stepNum++;
  const mid = Math.floor((low + high) / 2);
  document.getElementById('cmp-count').textContent = stepNum;

  if (low > high) {
    done = true;
    renderArray();
    showResult(false, -1);
    addLog(`<span style="color:var(--high)">Step ${stepNum}:</span> low (${low}) > high (${high}) — search space empty. Target <strong>${target}</strong> not found.`);
    endSearch();
    return;
  }

  renderArray(mid);

  if (arr[mid] === target) {
    done = true;
    renderArray(-1, mid);
    showResult(true, mid);
    addLog(`<span style="color:var(--found)">Step ${stepNum}:</span> mid=${mid}, arr[${mid}]=${arr[mid]} == target ${target} 🎯 <strong>FOUND at index ${mid}!</strong>`);
    endSearch();
  } else if (arr[mid] < target) {
    addLog(`Step ${stepNum}: low=<span style="color:var(--low)">${low}</span> mid=<span style="color:var(--mid)">${mid}</span> high=<span style="color:var(--high)">${high}</span> → arr[${mid}]=${arr[mid]} &lt; ${target}, so low → ${mid + 1}`);
    low = mid + 1;
  } else {
    addLog(`Step ${stepNum}: low=<span style="color:var(--low)">${low}</span> mid=<span style="color:var(--mid)">${mid}</span> high=<span style="color:var(--high)">${high}</span> → arr[${mid}]=${arr[mid]} &gt; ${target}, so high → ${mid - 1}`);
    high = mid - 1;
  }
}

function showResult(found, idx) {
  const banner = document.getElementById('result-banner');
  banner.className = 'rounded-2xl p-4 text-center font-bold text-lg mono';
  if (found) {
    banner.style.background = 'rgba(34,197,94,0.12)';
    banner.style.border = '1px solid rgba(34,197,94,0.4)';
    banner.style.color = 'var(--found)';
    banner.textContent = `✓  Found ${target} at index ${idx} in ${stepNum} step${stepNum > 1 ? 's' : ''}`;
  } else {
    banner.style.background = 'rgba(239,68,68,0.1)';
    banner.style.border = '1px solid rgba(239,68,68,0.35)';
    banner.style.color = 'var(--high)';
    banner.textContent = `✗  Target ${target} not found in array`;
  }
}

function endSearch() {
  document.getElementById('btn-next').disabled = true;
  document.getElementById('btn-auto').disabled = true;
  clearAuto();
}

function autoPlay() {
  if (done) return;
  document.getElementById('btn-auto').disabled = true;
  document.getElementById('btn-next').disabled = true;
  autoTimer = setInterval(() => {
    if (done) { clearAuto(); return; }
    nextStep();
  }, 900);
}

function clearAuto() {
  if (autoTimer) { clearInterval(autoTimer); autoTimer = null; }
}

function reset() {
  clearAuto();
  arr = []; low = 0; high = 0; stepNum = 0; done = false;
  document.getElementById('array-visual').innerHTML = '';
  document.getElementById('step-log').innerHTML =
    `<p class="mono text-sm" style="color:var(--muted)">Initialize a search to begin.</p>`;
  document.getElementById('cmp-count').textContent = '0';
  document.getElementById('max-steps').textContent = '—';
  document.getElementById('result-banner').className = 'hidden rounded-2xl p-4 text-center font-bold text-lg mono';
  document.getElementById('btn-next').disabled = true;
  document.getElementById('btn-auto').disabled = true;
}

window.onload = initSearch;
