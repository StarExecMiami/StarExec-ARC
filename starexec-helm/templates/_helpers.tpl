{{/* vim: set filetype=gotemplate: */}}
{{/*
Expand the name of the chart.
*/}}
{{- define "starexec.name" -}}
{{- default .Chart.Name .Values.nameOverride | trunc 63 | trimSuffix "-" }}
{{- end }}

{{/*
Create a default fully qualified app name.
We truncate at 63 chars because some Kubernetes name fields are limited to this (by the DNS naming spec).
If release name contains chart name it will be used as a full name.
*/}}
{{- define "starexec.fullname" -}}
{{- if .Values.fullnameOverride }}
{{- .Values.fullnameOverride | trunc 63 | trimSuffix "-" }}
{{- else }}
{{- $name := default .Chart.Name .Values.nameOverride }}
{{- if contains $name .Release.Name }}
{{- .Release.Name | trunc 63 | trimSuffix "-" }}
{{- else }}
{{- printf "%s-%s" .Release.Name $name | trunc 63 | trimSuffix "-" }}
{{- end }}
{{- end }}
{{- end }}

{{/*
Create chart name and version as used by the chart label.
*/}}
{{- define "starexec.chart" -}}
{{- printf "%s-%s" .Chart.Name .Chart.Version | replace "+" "_" | trunc 63 | trimSuffix "-" }}
{{- end }}

{{/*
Common labels
*/}}
{{- define "starexec.labels" -}}
helm.sh/chart: {{ include "starexec.chart" . }}
{{ include "starexec.selectorLabels" . }}
{{- if .Chart.AppVersion }}
app.kubernetes.io/version: {{ .Chart.AppVersion | quote }}
{{- end }}
app.kubernetes.io/managed-by: {{ .Release.Service }}
{{- end }}

{{/*
Selector labels
*/}}
{{- define "starexec.selectorLabels" -}}
app.kubernetes.io/name: {{ include "starexec.name" . }}
app.kubernetes.io/instance: {{ .Release.Name }}
{{- end }}

{{/*
Create the name of the service account to use
*/}}
{{- define "starexec.serviceAccountName" -}}
{{- if .Values.serviceAccount.create }}
{{- default (include "starexec.fullname" .) .Values.serviceAccount.name }}
{{- else }}
{{- default "default" .Values.serviceAccount.name }}
{{- end }}
{{- end }}

{{/*
Return the SSH secret name
*/}}
{{- define "starexec.sshSecretName" -}}
{{- if .Values.sshSecret.create }}
{{- default (printf "%s-ssh-key" (include "starexec.fullname" .)) .Values.sshSecret.secretName }}
{{- else }}
{{- required "existingSecretName must be provided if sshSecret.create is false" .Values.sshSecret.existingSecretName }}
{{- end }}
{{- end }}

{{/*
Return the TLS secret name
*/}}
{{- define "starexec.tlsSecretName" -}}
{{- if .Values.ingress.tls -}}
{{- $tls := first .Values.ingress.tls -}}
{{- if $tls.secretName -}}
{{- $tls.secretName -}}
{{- else -}}
{{- printf "%s-tls" (include "starexec.fullname" .) -}}
{{- end -}}
{{- else if .Values.ingress.createTlsSecret -}}
{{- default (printf "%s-tls" (include "starexec.fullname" .)) .Values.ingress.tlsSecretName -}}
{{- else -}}
{{- printf "%s-tls" (include "starexec.fullname" .) -}}
{{- end -}}
{{- end -}}
