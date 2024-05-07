import { parseProof, proofToGV } from './parser.js'

function choose(choices) {
	var index = Math.floor(Math.random() * choices.length);
	return choices[index];
}
window.choose = choose;

function htmlDecode(value) {
	let el = document.createElement("textarea");
	el.innerHTML = value;
	return el.innerText;
}

function showLoadingSpinner() {
	document.getElementById("loadingSymbol").classList.remove("hidden");
}

function hideLoadingSpinner() {
	document.getElementById("loadingSymbol").classList.add("hidden")
}



function ancestors(node, depth = 0, proofObj = window.proof){
	let l = [];
	let queue = [[node, depth]];

    let interpretationOffset = node.level;

	let nodeName;
	while(queue.length > 0){
		[node, depth] = queue.shift();
		let parents = node.parents.map(name => [proofObj[name], window.interpretation ? proofObj[name].level - interpretationOffset : depth-1]);
		l.push(...parents);
		queue.push(...parents);
	}

	return l;
}
window.ancestors = ancestors;


function descendants(node, depth = 0, proofObj = window.proof){
	let l = [];
	let queue = [[node, depth]];

    let interpretationOffset = node.level;

	let nodeName;
	while(queue.length > 0){
		[node, depth] = queue.shift();
		let children = node.children.map(name => [proofObj[name], window.interpretation ? proofObj[name].level - interpretationOffset : depth+1]);
		l.push(...children);
		queue.push(...children);
	}

	return l;
}
window.descendants = descendants;


function assignColorToNode(color, node) {
	try{
		node.graphviz.fillcolor = color;
		node.svgNode.style.fill = color;
	}
	catch(e){}
}

function nodeIsUninteresting(node){
	// the final conclusion is always interesting.
	if(node.children.length == 0){
		return false;
	}

	let anc = ancestors(originalProof[node.name], 0, originalProof).map(function(vals){return vals[0].role;})

	if (window.hideConjecture){
		if(["conjecture","negated_conjecture"].includes(node.role)){
			return true;
		}
		else if(anc.includes("conjecture") || anc.includes("negated_conjecture")){
			return true;
		}
	}

	return +node.info.interesting < window.interestFilterVal && ![-1, undefined].includes(+node.info.interesting);
}

//// begin graphviz setup ///////////////////////////
let graphviz = d3.select("#graph").graphviz();
window.graphviz = graphviz;

graphviz.zoomScaleExtent([0.01,100])

graphviz.transition(function () {
	return d3.transition("main").duration(500);
});

graphviz.engine("dot");
// graphviz.engine("neato");
// graphviz.engine("fdp");
// graphviz.engine("sfdp");
//// end graphviz setup /////////////////////////////


function getNodeName(hovered){
	return window.interpretation ? hovered.querySelector("text").getAttribute("proofKey") : hovered.querySelector("text").innerHTML;
}

function showGV(dot) {
	showLoadingSpinner()
	graphviz.renderDot(htmlDecode(dot));
	graphviz.on("end", function () {
		// add hover eventlisteners and update window.proof to tell
		// it where to find the svg nodes corresponding to "proof"/json nodes
		for (let node of document.querySelectorAll("g.node")) {
			node.addEventListener("mouseenter", nodeHoverEventListener);
			let nodeName = getNodeName(node);
			try{
				window.proof[nodeName].svgNode = node.querySelector("polygon, ellipse");
			}
			catch(e){
				window.nodeName = nodeName;
			}
		}
		hideLoadingSpinner();
	});
}



function nodeHoverEventListener(e) {
	if (e.buttons != 0) {
		return
	}
	let nodeName = getNodeName(e.currentTarget);
	let node = proof[nodeName];

	let nodeInfo = document.getElementById("nodeInfo");
	let tptpTextareaOpen = "";
	try{
		tptpTextareaOpen = document.getElementById("tptpNodeStatement").classList.contains("open") ? "open" : "";
	}catch(e){}

	let interestingnessHTML = "";
	if (node.info.interesting != undefined){
		interestingnessHTML = `<b>Interestingness: </b>${node.info.interesting}<br>`;
	}

	nodeInfo.innerHTML = `<hr>
		<b>Name:</b> ${node['name']}<br>
		<b>Type:</b> ${node['type']}<br>
		<b>Role:</b> ${node['role']}<br>
		${interestingnessHTML}
		<b>Formula:</b> ${node['formula']}<br>
		<b>Inference Record:</b> ${node['inference_record']}
		<hr>

		<div class="box">
			<h4 id="tptpNodeStatement" 
				class="settingsHeader ${tptpTextareaOpen}" 
				onclick="collapseBox(this)">
					Full TPTP Statement: 
					<span class="triangle"></span>
			</h4>
			<textarea id="tptpTextarea" class="${tptpTextareaOpen}">${node['tptp']}</textarea>
		</div>
  `

	recolorNodesByInterest()

	function colorHelper(depth, min, max) {
		let startColor = [255, 0, 0];
		let midColor = [255, 255, 255];
		let endColor = [0, 0, 255];
		let frac, r, g, b
		if (depth < 0) {
			frac = (depth - min) / (0 - min);
			r = Math.round(startColor[0] + frac * (midColor[0] - startColor[0]));
			g = Math.round(startColor[1] + frac * (midColor[1] - startColor[1]));
			b = Math.round(startColor[2] + frac * (midColor[2] - startColor[2]));
		}
		else if (depth > 0) {
			frac = 1 - (max - depth) / max
			r = Math.round(midColor[0] + frac * (endColor[0] - midColor[0]));
			g = Math.round(midColor[1] + frac * (endColor[1] - midColor[1]));
			b = Math.round(midColor[2] + frac * (endColor[2] - midColor[2]));
		}
		else {
			[r, g, b] = midColor;
		}

		function hex(v) { return v.toString(16).length == 2 ? v.toString(16) : "0" + v.toString(16); }
		return `#${hex(r)}${hex(g)}${hex(b)}`;
	}


	let anc = ancestors(node);
	let minDepth = 0;
	anc.forEach(function (a) {
		if (a[1] < minDepth) {
			minDepth = a[1];
		}
	});

	let des = descendants(node);
	let maxDepth = 0;
	des.forEach(function (d) {
		if (d[1] > maxDepth) {
			maxDepth = d[1];
		}
	});


	for (let [a, depth] of anc) {
		if(a.graphviz.fillcolor != "#000000")
			assignColorToNode(colorHelper(depth, minDepth, maxDepth), a);
	}
	for (let [d, depth] of des) {
		if(d.graphviz.fillcolor != "#000000")
			assignColorToNode(colorHelper(depth, minDepth, maxDepth), d);
	}

	if(node.graphviz.fillcolor != "#000000")
		assignColorToNode(colorHelper(0, minDepth, maxDepth), node);
}


//// begin interestingness helpers /////////////////
function assignInterestingnessToHeightAndWidth() {
	for (let node of Object.values(window.proof)) {
		if (window.interestScalingBool && node.info.interesting !== undefined) {
			node.graphviz.width = scaleFromInterestingness(node.info.interesting);
			node.graphviz.height = scaleFromInterestingness(node.info.interesting);
		}
		else {
			node.graphviz.width = undefined;
			node.graphviz.height = undefined;
		}
	}
}
window.assignInterestingnessToHeightAndWidth = assignInterestingnessToHeightAndWidth;


function getInterest() {
	showLoadingSpinner();
	Array.from(document.querySelectorAll(".interestHidden")).map(x => x.style.display = "block");
	if(!window.interestScalingBool){
		toggleInterestScaling();
	}

	fetch("/idv/interestingness", {
		method: 'POST',
		body: JSON.stringify({
			"proof": document.getElementById("proofText").innerText
		})
	})
	.then(response => response.text())
	.then(function (response) { console.log(response); return response })
	.then(function (text) {
		text = htmlDecode(text);
		let interestProof = parseProof(text);

		for (let key of Object.keys(originalProof)) {
			originalProof[key].info.interesting = interestProof[key].info.interesting;
		}
		redrawNodesByInterest();
	})
	.catch(function(v){alert("Failed to query TPTP for interestingness!");})
	.finally(function(v) {hideLoadingSpinner()});
}
window.getInterest = getInterest;



function toggleInterestScaling() {
	let el = document.querySelector("#interestScaleToggle");
	if (el.innerText.includes("Disable")) {
		el.innerText = el.innerText.replace("Disable", "Enable");
	}
	else {
		el.innerText = el.innerText.replace("Enable", "Disable");
	}
	window.interestScalingBool = !window.interestScalingBool;
	renderInterest();
}
window.toggleInterestScaling = toggleInterestScaling;



function renderInterest() {
	assignInterestingnessToHeightAndWidth();
	showGV(proofToGV(window.proof));
}
window.renderInterest = renderInterest;


function recolorNodesByInterest() {
	window.interestFilterVal = document.getElementById("interestingnessSlider").value;

	for(let key of Object.keys(proof)){
		let node = proof[key];
		if(nodeIsUninteresting(node)){
			assignColorToNode("#000000", node);
		}
		else{
			assignColorToNode("#c0c0c0", node);
		}
	}

	assignInterestingnessToHeightAndWidth();
}
window.recolorNodesByInterest = recolorNodesByInterest;

function redrawNodesByInterest(){
	window.interestFilterVal = document.getElementById("interestingnessSlider").value;
	window.proof = JSON.parse(JSON.stringify(originalProof));
	assignInterestingnessToHeightAndWidth();

	for (let node of Object.values(window.proof)) {
		// make node invisible if it's too uninteresting.
		if (nodeIsUninteresting(node)) {
			
			// update parent nodes
			for(let parentName of node.parents){
				let parent = proof[parentName];
				parent.children.splice(parent.children.indexOf(node.name), 1);
				parent.children.push(...node.children);
				parent.children = Array.from(new Set(parent.children));
			}

			// update children nodes
			for(let childName of node.children){
				let child = proof[childName];
				child.parents.splice(child.parents.indexOf(node.name), 1);
				child.parents.push(...node.parents);
				child.parents = Array.from(new Set(child.parents));
			}

			delete window.proof[node.name];
		}
	}

	showGV(proofToGV(window.proof));
}
window.redrawNodesByInterest = redrawNodesByInterest;

function resetGraph(){
	document.getElementById('interestingnessSlider').value=-1;
	let hideConjNodesButton = document.getElementById('hideConjNodesButton');
	hideConjNodesButton.innerText = hideConjNodesButton.innerText.replace("Show","Blacken");
	window.hideConjecture = false;
	redrawNodesByInterest()
}
window.resetGraph = resetGraph;

function toggleConjectureVisible(el) {
	if (el.innerText.includes("Blacken")) {
		el.innerText = el.innerText.replace("Blacken", "Show");
	}
	else {
		el.innerText = el.innerText.replace("Show", "Blacken");
	}

	window.hideConjecture = !window.hideConjecture;
	recolorNodesByInterest();
}
window.toggleConjectureVisible = toggleConjectureVisible;


//// end interestingness helpers ///////////////////




window.parseProof = parseProof
window.proofToGV = proofToGV
window.showGV = showGV;



window.collapseBox = function (title) {
	let el = title.parentNode.children[1];
	let open = title.classList.contains("open");

	if(open){
		title.classList.remove("open");
		el.style.height = "0px";
		el.style.display = "none";
	}
	else{
		title.classList.add("open");
		el.style.height = "100%";	
		el.style.display = "block";
	}

}
